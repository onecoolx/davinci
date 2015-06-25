/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2006 Michael Emmel mike.emmel@gmail.com 
 * Copyright (C) 2007 Alp Toker <alp.toker@collabora.co.uk>
 * Copyright (C) 2007 Holger Hans Peter Freyther
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "ResourceHandleManagerCurl.h"
#include "ResourceError.h"
#include "ResourceHandle.h"
#include "ResourceHandleInternalCurl.h"
#include "DownloadResourceClient.h"

#include "CookieJar.h"
#include "ProxyPlatform.h"
#include "FtpProtocolHandler.h"
#include "HttpProtocolHandler.h"
#include "FileProtocolHandler.h"
#include "DataProtocolHandler.h"
#include "AboutProtocolHandler.h"
#include "CacheManager.h"
#if ENABLE(SSL)
#include "CertificateMC.h"
#endif

#if PLATFORM(UNIX)
#include <errno.h>
#endif

#if PLATFORM(WIN32) || PLATFORM(WINCE)
#include <windows.h>
#endif

#include "WebCallback.h"
#include "Debug.h"

namespace WebCore {

const int selectTimeoutMS = 5;
const double pollTimeSeconds = 0.05;
const int maxRunningJobs = 8;

ResourceHandleManager::ResourceHandleManager()
    : m_downloadTimer(this, &ResourceHandleManager::downloadTimerCallback)
#if ENABLE(HTTPCACHE)
	, m_cacheReaderTimer(this, &ResourceHandleManager::cacheTimerCallback)
	, m_cachingJobs(0)
#endif
    , m_runningJobs(0)
{
    curl_global_init_mem(CURL_GLOBAL_ALL, (curl_malloc_callback)fastMalloc,
            (curl_free_callback)fastFree, (curl_realloc_callback)fastRealloc,
            (curl_strdup_callback)fastStrdup, (curl_calloc_callback)fastCalloc);
    m_curlMultiHandle = curl_multi_init();
	curl_multi_setopt(m_curlMultiHandle, CURLMOPT_MAXCONNECTS, 16);
    m_curlShareHandle = curl_share_init();
    curl_share_setopt(m_curlShareHandle, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);

    m_authJar.clear();
}

ResourceHandleManager::~ResourceHandleManager()
{
	curl_multi_cleanup(m_curlMultiHandle);
	curl_share_cleanup(m_curlShareHandle);
	curl_global_cleanup();
    m_authJar.clear();
}

void ResourceHandleManager::removeAll()
{
#if ENABLE(HTTPCACHE)
	if (m_cacheReaderTimer.isActive())
		m_cacheReaderTimer.stop();
#endif

	if (m_downloadTimer.isActive())
		m_downloadTimer.stop();

	for (size_t i = 0; i < m_resourceHandleList.size(); i++)
		removeResourceHandle(m_resourceHandleList[i]);

	m_resourceHandleList.clear();
	
#if ENABLE(HTTPCACHE)
	for (size_t j = 0; j < m_cacheHandleList.size(); j++)
		removeCachedResourceHandle(m_cacheHandleList[j]);

	m_cacheHandleList.clear();
#endif
}

void ResourceHandleManager::releaseAllResourceJobs()
{
	ResourceHandleManager::sharedInstance()->removeAll();
}

ResourceHandleManager* ResourceHandleManager::sharedInstance()
{
    static ResourceHandleManager* sharedInstance = 0;
    if (!sharedInstance)
        sharedInstance = new ResourceHandleManager();
    return sharedInstance;
}

static void dealWithFail(ResourceHandle* job, CURLMsg* msg)
{
    long responseCode = 0;
    ResourceErrorType errorType = NoType;
    ResourceHandleInternal* d = job->getInternal();

    curl_easy_getinfo(d->m_handle, CURLINFO_RESPONSE_CODE, &responseCode);
    if (responseCode) {
        if (job->request().url().isHttp())
            errorType = HttpNetError;
        else if (job->request().url().isFtp())
            errorType = FtpNetError;
    } else { 
        errorType = CurlNetError;
        responseCode = msg->data.result;
    }

    ResourceError error(responseCode, job->request().url().url().ascii(), errorType);
    if (d->client())
        d->client()->didFail(job, error);
}

#if ENABLE(HTTPCACHE)
void ResourceHandleManager::cacheTimerCallback(Timer<ResourceHandleManager>* timer)
{
	for (size_t i = 0; i < m_cacheHandleList.size(); i++) {
		ResourceHandle* job = m_cacheHandleList[i];
		if (job) {
			ResourceHandleInternal* d = job->getInternal();

			if (d->m_cancelled) {
				m_cacheHandleList[i] = 0;
				job->deref();
				m_cachingJobs--;
				continue;
			}

			ResourceHandleClient * client = d->client();
			size_t size = 0;
			unsigned char* p = job->getInternal()->m_cacheEntry.getData(&size);
			
			responseMIMETypeCheck(job, p, size);

			if (!d->m_response.responseFired()) {
				if (client)
					client->didReceiveResponse(job, d->m_response);
				d->m_response.setResponseFired(true);
			}

			if (d->m_cancelled) {
				m_cacheHandleList[i] = 0;
				job->deref();
				m_cachingJobs--;
				continue;
			}

			if (!p || !size) {
				if (client)
					client->didFinishLoading(job);
				m_cacheHandleList[i] = 0;
				job->deref();
				m_cachingJobs--;
			} else {
				if (client)
					client->didReceiveData(job, reinterpret_cast<char*>(p), size, 0);
			}
		}
	}

	if (!m_cachingJobs) 
		m_cacheHandleList.clear();

    if (!m_cacheReaderTimer.isActive() &&  m_cacheHandleList.size())
        m_cacheReaderTimer.startOneShot(pollTimeSeconds);
}
#endif

void ResourceHandleManager::downloadTimerCallback(Timer<ResourceHandleManager>* timer)
{
    startScheduledJobs();

    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = 0;

    struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = selectTimeoutMS * 2000;       // select waits microseconds
    
    // Temporarily disable timers since signals may interrupt select(), raising EINTR errors on some platforms
    setDeferringTimers(true);
    int rc = 0;
	{  
		FD_ZERO(&fdread);
        FD_ZERO(&fdwrite);
        FD_ZERO(&fdexcep);
        curl_multi_fdset(m_curlMultiHandle, &fdread, &fdwrite, &fdexcep, &maxfd);
        // When the 3 file descriptors are empty, winsock will return -1
        // and bail out, stopping the file download. So make sure we
        // have valid file descriptors before calling select.
        if (maxfd >= 0)
            rc = ::select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
	}
    setDeferringTimers(false);

	if (-1 == rc) {
#if PLATFORM(UNIX)
		if (!m_downloadTimer.isActive() && errno != EINTR)
#elif PLATFORM(WIN32) || PLATFORM(WINCE)
		if (!m_downloadTimer.isActive() && WSAGetLastError() != WSAEINTR)
#else
#error don't know how to get select error!
#endif
			m_downloadTimer.startOneShot(pollTimeSeconds);
		return;
	}

	int runningHandles = 0;
	while (curl_multi_perform(m_curlMultiHandle, &runningHandles) == CURLM_CALL_MULTI_PERFORM) { }

	// check the curl messages indicating completed transfers
	// and free their resources
	while (true) {
		int messagesInQueue;
		CURLMsg* msg = curl_multi_info_read(m_curlMultiHandle, &messagesInQueue);
		if (!msg)
			break;

		if (CURLMSG_DONE != msg->msg)
			continue;

		// find the node which has same d->m_handle as completed transfer
		CURL* handle = msg->easy_handle;
		ASSERT(handle);
		ResourceHandle* job = 0;
		CURLcode err = curl_easy_getinfo(handle, CURLINFO_PRIVATE, &job);
		if ((CURLE_OK != err) || !job)
			continue;

		ResourceHandleInternal* d = job->getInternal();
		if (d->m_cancelled) {
			removeResourceHandle(job);
			continue;
		}

		ASSERT(d->m_handle == handle);
		if (CURLE_OK == msg->data.result || msg->data.result == CURLE_PARTIAL_FILE) {
			if (isAuthentication(d->m_response.httpStatusCode()) && d->m_authenticate) {
				doAuth(job);
				continue;
			}

#if ENABLE(HTTPCACHE)
			if (d->client() && !isUseCacheData(d->m_response.httpStatusCode()))
#else
			if (d->client())
#endif
				d->client()->didFinishLoading(job);
		} else {
#ifndef NDEBUG
			char* url = 0;
			curl_easy_getinfo(d->m_handle, CURLINFO_EFFECTIVE_URL, &url);
			printf("Curl ERROR for url='%s', error: '%s'\n", url, curl_easy_strerror(msg->data.result));
#endif
			dealWithFail(job, msg);
		}
		removeResourceHandle(job);
	}

    bool started = startScheduledJobs(); // new jobs might have been added in the meantime

    if (!m_downloadTimer.isActive() && (started || (runningHandles > 0)))
        m_downloadTimer.startOneShot(pollTimeSeconds);

#if ENABLE(HTTPCACHE)
	if (!started && !runningHandles)
		CacheManager::sharedInstance()->saveIfNeeded();	
#endif
}

void ResourceHandleManager::removeFromCurl(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
    if (!d->m_handle)
        return;

    m_runningJobs--;
    curl_multi_remove_handle(m_curlMultiHandle, d->m_handle);
    curl_easy_cleanup(d->m_handle);
    d->m_handle = 0;
    d->m_hasCurlHandle = false;
    d->m_forSavingResource = false;
}

void ResourceHandleManager::removeResourceHandle(ResourceHandle* job)
{
    removeFromCurl(job);
    job->deref();
}

#if ENABLE(HTTPCACHE)
void ResourceHandleManager::removeCachedResourceHandle(ResourceHandle* job)
{
	if (job)
		job->deref();
}

void ResourceHandleManager::addCacheLoading(ResourceHandle* job)
{
	job->ref();
	
	job->getInternal()->m_cacheEntry.resetReader(); //reset reader to first;
	job->getInternal()->m_cacheReader = true; // for cancel
	m_cacheHandleList.append(job);
	m_cachingJobs++;
	if (!m_cacheReaderTimer.isActive())
		m_cacheReaderTimer.startOneShot(pollTimeSeconds);
}
#endif

void ResourceHandleManager::add(ResourceHandle* job)
{
    ASSERT(job);

    ResourceHandleInternal* d = job->getInternal();
    if (d->m_asyncDownload) {
        // we can be called from within curl, so to avoid re-entrancy issues
        // schedule this job to be added the next time we enter curl download loop
        m_resourceHandleList.append(job);
        if (!m_downloadTimer.isActive())
            m_downloadTimer.startOneShot(pollTimeSeconds);
        return;
    }

    initJob(job);
}

bool ResourceHandleManager::removeScheduledJob(ResourceHandle* job)
{
    int size = m_resourceHandleList.size();
    for (int i=0; i < size; i++) {
        if (job == m_resourceHandleList[i]) {
            m_resourceHandleList.remove(i);
            return true;
        }
    }
    return false;
}

bool ResourceHandleManager::startScheduledJobs()
{
    // TODO: Create a separate stack of jobs for each domain.

    bool started = false;
    while (!m_resourceHandleList.isEmpty() && m_runningJobs < maxRunningJobs) {
        ResourceHandle* job = m_resourceHandleList[0];
        if (startAsyncJob(job)) {
            m_resourceHandleList.remove(0);
            started = true;
        }
    }
    return started;
}

bool ResourceHandleManager::startAsyncJob(ResourceHandle* job)
{
    KURL url = job->request().url();
    if (equalIgnoringCase(url.protocol(), "data")) {
        parseDataUrl(job);
        job->deref();
        return true;
    } else if (equalIgnoringCase(url.protocol(), "about")) {
        handleAboutUrl(job);
        job->deref();
        return true;
    }

    initJob(job);

    ResourceHandleInternal* d = job->getInternal();
    
    m_runningJobs++;
    // don't call perform, because events must be async
    // timeout will occur and do curl_multi_perform
    CURLMcode ret = curl_multi_add_handle(m_curlMultiHandle, d->m_handle);
    if (ret && ret != CURLM_CALL_MULTI_PERFORM) {
#ifndef NDEBUG
        printf("Error %d starting job %s\n", ret, job->request().url().url().ascii());
#endif
        job->cancel();
        return false;
    }
    return true;
}

void ResourceHandleManager::startSyncJob(ResourceHandle* job)
{
    ASSERT(job);
    ResourceHandleInternal* d = job->getInternal();
    CURLcode err = curl_easy_perform(d->m_handle);

    if (CURLE_OK == err) {
        if (d->client())
            d->client()->didFinishLoading(job);
    } else {
        CURLMsg msg;
        dealWithFail(job, &msg);
    }
    curl_easy_cleanup(d->m_handle);
    d->m_handle = 0;
    job->deref();
}

void ResourceHandleManager::initJob(ResourceHandle* job)
{
    ASSERT(job);
    ResourceHandleInternal* d = job->getInternal();

    if (d->m_hasCurlHandle)
        return;

    d->m_handle = curl_easy_init();
    d->m_hasCurlHandle = true;

#if !PLATFORM(WINCE)
    if (getenv("DEBUG_CURL")) {
		curl_easy_setopt(d->m_handle, CURLOPT_STDERR, stderr);
        curl_easy_setopt(d->m_handle, CURLOPT_VERBOSE, 1);
	}
#endif

#if ENABLE(SSL)
#if ENABLE(SSLFILE)
    if (!caPath().isNull())
        curl_easy_setopt(d->m_handle, CURLOPT_CAPATH, caPath().data());
#endif
    curl_easy_setopt(d->m_handle, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(d->m_handle, CURLOPT_SSL_VERIFYHOST, 0);
#endif
    
    KURL url = job->request().url();
    if (d->m_authPwd.isNull()) 
        d->m_authPwd = m_authJar.get(url.host());

    if (url.isHttp())
        initHttpJob(job);
    else if (url.isFtp())
        initFtpJob(job);
    else if (url.isLocalFile())
        initFileJob(job);
    else
        initHttpJob(job);

    if (proxyEnabled()) {
        ProxyItem proxyItem = proxy(url); 
        if (!proxyItem.m_host.isNull()) {
			d->m_proxyHost = new char[proxyItem.m_host.length()+1];
			d->m_proxyHost = strncpy(d->m_proxyHost, proxyItem.m_host.data(), proxyItem.m_host.length()+1);
            curl_easy_setopt(d->m_handle, CURLOPT_PROXY, d->m_proxyHost);

            const char *port = proxyItem.m_port.data();
            if (port)
                curl_easy_setopt(d->m_handle, CURLOPT_PROXYPORT, atol(port));

            curl_easy_setopt(d->m_handle, CURLOPT_PROXYTYPE, proxyItem.m_type);

            if (!proxyItem.m_user.isNull() && (proxyItem.m_user != CString(""))) {
               	d->m_proxyUserPwd = new char[proxyItem.m_user.length() + proxyItem.m_password.length() + 2];
                d->m_proxyUserPwd = strncpy(d->m_proxyUserPwd, proxyItem.m_user.data(), proxyItem.m_user.length()+1);
                if (!proxyItem.m_password.isNull() && (proxyItem.m_password != CString(""))) {
                    d->m_proxyUserPwd = strcat(d->m_proxyUserPwd, ":");
                    d->m_proxyUserPwd = strcat(d->m_proxyUserPwd, proxyItem.m_password.data());
                }
                curl_easy_setopt(d->m_handle, CURLOPT_PROXYUSERPWD, d->m_proxyUserPwd);
            }

            curl_easy_setopt(d->m_handle, CURLOPT_HTTPPROXYTUNNEL, 1);
        }
    }

    curl_easy_setopt(d->m_handle, CURLOPT_ERRORBUFFER, m_curlErrorBuffer);
    curl_easy_setopt(d->m_handle, CURLOPT_DNS_CACHE_TIMEOUT, 60*3); // 3 minutes
    curl_easy_setopt(d->m_handle, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(d->m_handle, CURLOPT_SHARE, m_curlShareHandle);
}

void ResourceHandleManager::passCurlToNewResourceHandle(ResourceHandle* old)
{
    DownloadResourceClient *client = 0;
    ResourceHandleInternal* d = old->getInternal();
    if (!d->m_hasDownloadClient)
        client = new DownloadResourceClient(true);
    else
        client = static_cast<DownloadResourceClient*>(old->client());

    RefPtr<ResourceHandle> job = ResourceHandle::create(old->request(), client, false, true, true);
    d = job->getInternal();
    d->m_hasDownloadClient = true;
    d->m_forSavingResource = true;
    d->m_mightDownloadFromHandle = true;

    d->m_handle = old->getInternal()->m_handle;
    d->m_hasCurlHandle = true;

    curl_easy_setopt(d->m_handle, CURLOPT_PRIVATE, job.get());
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEDATA, job.get());
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEHEADER, job.get());
}

void ResourceHandleManager::cancel(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
#if ENABLE(HTTPCACHE)
    if (d->needsResourceHandleForDownloading() && !d->isCacheReader())
#else
    if (d->needsResourceHandleForDownloading())
#endif
        passCurlToNewResourceHandle(job);

    if (removeScheduledJob(job))
        return;

    if (!(d->m_mightDownloadFromHandle && d->m_forSavingResource))
        d->m_cancelled = true;

#if ENABLE(HTTPCACHE)
	if (d->isCacheReader()) {
    	if (!m_cacheReaderTimer.isActive())
        	m_cacheReaderTimer.startOneShot(pollTimeSeconds);
	} else {
#endif
    if (!m_downloadTimer.isActive())
        m_downloadTimer.startOneShot(pollTimeSeconds);
#if ENABLE(HTTPCACHE)
	}
#endif
}

void ResourceHandleManager::doAuth(ResourceHandle* job)
{
    char user[128];
    char pass[128];
    char *userPass = NULL; 
    int isOk = 0;
    int len;

    removeScheduledJob(job);
    removeFromCurl(job);

    ResourceHandleInternal* d = job->getInternal();

    if (MaCross::cb_provide_auth) {
        memset(user, 0, sizeof(user));
        memset(pass, 0, sizeof(pass));
        String strTitle = d->m_response.httpHeaderField("WWW-Authenticate");
        int pos = strTitle.find('=');
        if (pos != -1)
            strTitle = strTitle.substring(pos+1, strTitle.length()-pos-1);
        isOk = MaCross::cb_provide_auth(strTitle.deprecatedString().utf8(), user, 128, pass, 128);
    }

    if (isOk) {
        if (strlen(user) && strlen(pass)) {
            len = strlen(user) + strlen(pass);
            userPass = (char *)malloc(len+2);
            if (userPass) {
                memset(userPass, 0, sizeof (userPass));
                strcpy(userPass, user);
                strcat(userPass, ":");
                strcat(userPass, pass);
                CString auth(userPass, strlen(userPass));
                d->m_authPwd = auth;
                m_authJar.set(job->request().url().host(), auth);
                free(userPass);
            }
        }
    } else
        d->m_authenticate = false;
    add(job);
}

} /* namespace WebCore */
