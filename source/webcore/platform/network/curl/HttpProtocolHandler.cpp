
#include "config.h"
#include <wtf/Vector.h>
#include <wtf/StringExtras.h>
#include "CString.h"
#include "Debug.h"
#include "HTTPParsers.h"
#include "CookieJar.h"
#include "MIMETypePlatform.h"
#include "MIMETypeRegistry.h" 
#include "ResourceHandle.h"
#include "ResourceHandleClient.h"
#include "ResourceHandleInternalCurl.h"
#include "FileSystem.h"
#if ENABLE(PLUGIN)
#include "PlugInInfoStore.h"
#endif
#include "ResourceHandleManagerCurl.h"
#include "DownloadResourceClient.h"
#include "HttpProtocolHandler.h"
#include "CacheManager.h" 

namespace WebCore {

static size_t readCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    ResourceHandle* job = static_cast<ResourceHandle*>(data);
    ResourceHandleInternal* d = job->getInternal();
    
    if (d->m_cancelled)
        return CURL_READFUNC_ABORT;

    size_t leftSize = 0;
    size_t readingSize = size*nmemb;
    Vector<FormDataElement> elements = job->request().httpBody()->elements();

NextElement:
    size_t elementSize = elements.size();
    if (d->m_formElement >= elementSize)
        return 0;

    long   dataSize = 0;
    if (elements[d->m_formElement].m_type == FormDataElement::data)
        dataSize = elements[d->m_formElement].m_data.size();
#if ENABLE(FILESYSTEM)
    else        
        fileSize(elements[d->m_formElement].m_filename, dataSize);
#endif
    if (! dataSize) {
        d->m_formElement++;
        d->m_readedFormSize = 0;
        goto NextElement;
    }

    leftSize =  dataSize - d->m_readedFormSize;
    if (leftSize == 0 && d->m_formElement == elementSize)
        return CURL_READFUNC_ABORT;

    if (! leftSize) {
        d->m_formElement++;
        d->m_readedFormSize = 0;
    }

    long oldIndex = d->m_formElement;
    size_t offset = d->m_readedFormSize;
    size_t readedSize = 0;
    if (leftSize <= readingSize) {
        d->m_formElement++;
        d->m_readedFormSize = 0;
        readedSize = leftSize;
    }
    else {
        readedSize = readingSize;
        d->m_readedFormSize += readedSize;
    }

    if (elements[oldIndex].m_type == FormDataElement::data)
        memcpy(ptr, &elements[oldIndex].m_data.data()[offset], readedSize);
#if ENABLE(FILESYSTEM)
    else
        readFile((unsigned char*)ptr, elements[oldIndex].m_filename, offset, readedSize);
#endif
    return readedSize;
}

static void setResponseDate(ResourceHandle* handle) 
{
	ResourceHandleInternal* job = handle->getInternal();
	ResourceResponse &response = job->m_response;
	String lastModified;
	String eTag;
	time_t expr_time = 86400; //default 24 hours

    String str = response.httpHeaderField("Last-Modified");
    if (! str.isEmpty()) {
		lastModified = str;
        time_t tm = curl_getdate(lastModified.latin1().data(), NULL);
		expr_time = (time(0)-tm)/10; //mozilla special
        response.setLastModifiedDate(tm);
    }

    str = response.httpHeaderField("ETag");
    if (! str.isEmpty()) {
		eTag = str;
    }

    str = response.httpHeaderField("Expires");
    if (! str.isEmpty()) {
        time_t tm = curl_getdate(str.latin1().data(), NULL);
		expr_time = tm-time(0);
        response.setExpirationDate(tm);
    }

    str = response.httpHeaderField("Cache-Control");
    if (str.contains("no-cache", false) || str.contains("no-store", false)) {
        response.setExpirationDate(time(0));
        return;
    }

    int pos = str.find("max-age=", false);
    if (-1 != pos) {
        int sec = atoi(str.substring(pos+8, str.length()-pos-8).latin1().data()); 
		expr_time = sec;
        response.setExpirationDate(time(0) + sec);
    }

	if (expr_time < 0) expr_time = 0;

#if ENABLE(HTTPCACHE)
	// if Last-Modified and ETag and not Expires make Cache Entry for job
	if (CacheManager::sharedInstance()->cacheEnabled()) {

		if (!expr_time) return; //no age not need cache

		ResourceHandleClient * client = handle->client();
		if (client) {
			CacheStoragePolicy policy = StorageAllowed;
			client->willCacheResponse(handle, policy);
			if (policy != StorageAllowed)
				return;
		}

		str = response.httpHeaderField("Content-Length");
    	if (str.isEmpty()) // Transfer-Encoding: chunked
			return;

		size_t len = (size_t)atoi(str.latin1().data());
		if (!len)
			return; // no content length
		
		str = response.httpHeaderField("Content-Type");

    	if (str.isEmpty()) // no content type
			return;

		if (!job->m_cacheEntry.isValid()){
			// create a new entry for this job
			job->m_cacheEntry = CacheEntry::createEntry(response.url(), lastModified, eTag, str, len, expr_time);
		} else {
			// update the entry for new data.
			CacheEntry::updateEntry(job->m_cacheEntry, lastModified, eTag, str, expr_time);
		}		
	}
#endif
}

static bool downloadAttachment(ResourceResponse& response)
{
    String field = response.httpHeaderField("Content-Disposition");
    if (field.startsWith("inline", false))
        return false;

    if (! field.isEmpty())
        return true;

    return false;
}

static void handleHttpHeader(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();

    d->m_response.setMimeType(extractMIMETypeFromMediaType(d->m_response.httpHeaderField("Content-Type").lower()));
    d->m_response.setTextEncodingName(extractCharsetFromMediaType(d->m_response.httpHeaderField("Content-Type")));
    d->m_response.setSuggestedFilename(filenameFromHTTPContentDisposition(d->m_response.httpHeaderField("Content-Disposition")));

    setResponseDate(job);
}

static void processCacheData(ResourceHandle* job)
{
#if ENABLE(HTTPCACHE)
    ResourceHandleInternal* d = job->getInternal();

    d->m_response.setMimeType(extractMIMETypeFromMediaType(d->m_cacheEntry.getContentType().lower()));
    d->m_response.setTextEncodingName(extractCharsetFromMediaType(d->m_cacheEntry.getContentType()));
	//FIXME: need Content-Disposit for download
	ResourceHandleManager::sharedInstance()->addCacheLoading(job);
#endif
}

static void initJobEntry(const KURL& url, ResourceHandle* job)
{
#if ENABLE(HTTPCACHE)
	if (CacheManager::sharedInstance()->cacheEnabled()) {
		ResourceHandleInternal* d = job->getInternal();
		if (d->m_request.cachePolicy() == ReloadIgnoringCacheData)
			return;

		CacheEntry entry = CacheEntry::queryEntry(url);
		if (entry.isValid()) {
			d->m_cacheEntry = entry;

			String str = entry.getLastModify();
			if (!str.isEmpty()) {
				d->m_request.setHTTPHeaderField("If-Modified-Since", str);
			}

			str = entry.getETag();
			if (!str.isEmpty()) {
				d->m_request.setHTTPHeaderField("If-None-Match", str);
			}
		}
	}
#endif
}

/*
 * This is being called for each HTTP header in the response. This includes '\r\n'
 * for the last line of the header.
 *
 * We will add each HTTP Header to the ResourceResponse and on the termination
 * of the header (\r\n) we will parse Content-Type and Content-Disposition and
 * update the ResourceResponse and then send it away.
 *
 */
static size_t httpHeaderCallback(char* ptr, size_t size, size_t nmemb, void* data)
{
    ResourceHandle* job = static_cast<ResourceHandle*>(data);
    ResourceHandleInternal* d = job->getInternal();
    if (d->m_cancelled)
        return 0;

    size_t totalSize = size * nmemb;
    ResourceHandleClient* client = d->client();
    if (!client)
        return totalSize;

    String header(static_cast<const char*>(ptr), totalSize);

    /*
     * a) We can finish and send the ResourceResponse
     * b) We will add the current header to the HTTPHeaderMap of the ResourceResponse 
     */
    if (header == String("\r\n") || header == String("\r") || header == String("\n")) {
        CURL* h = d->m_handle;
        CURLcode err;
        d->m_response.setExpectedContentLength(atoll(d->m_response.httpHeaderField("Content-Length").deprecatedString().latin1()));

        const char* hdr;
        err = curl_easy_getinfo(h, CURLINFO_EFFECTIVE_URL, &hdr);
        
        long httpCode = 0;
        err = curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &httpCode);
        d->m_response.setHTTPStatusCode(httpCode);
        if (isServerRedirection(httpCode)) {
            KURL newURL = KURL(job->request().url(), d->m_response.httpHeaderField("Location").deprecatedString());
            if (cookiesEnabled()) {
                String strCookie = cookies(newURL);
                if (strCookie.isEmpty())
                    strCookie = cookies(KURL(hdr));
                if (!strCookie.isEmpty()) {
                    if (d->m_cookie)
                        fastFree(d->m_cookie);
                    d->m_cookie = (char*)fastStrdup(strCookie.latin1().data());
                    curl_easy_setopt(d->m_handle, CURLOPT_COOKIE, d->m_cookie);
                }
            }

            ResourceRequest redirectedRequest = job->request();
            redirectedRequest.setURL(newURL);
            if (client)
                client->willSendRequest(job, redirectedRequest, d->m_response);
            d->m_response.setUrl(newURL);
        }
        else
            d->m_response.setUrl(KURL(hdr));

		if (isUseCacheData(httpCode)) 
			processCacheData(job);
		else 
        	handleHttpHeader(job);
    
    } else {
        int splitPos = header.find(":");
        if (splitPos != -1) {
            String strKey = header.left(splitPos);
            String strValue = header.substring(splitPos+1).stripWhiteSpace();
            if (equalIgnoringCase(strKey , "Set-Cookie") || (equalIgnoringCase(strKey , "Set-Cookie2"))) { 
                if (cookiesEnabled()) {
                    const char* hdr;
                    curl_easy_getinfo(d->m_handle, CURLINFO_EFFECTIVE_URL, &hdr);
                    setCookies(hdr, NULL, strValue);
                }
            }
            else
                d->m_response.setHTTPHeaderField(strKey, strValue);
        }
    }
    return totalSize;
}

void responseMIMETypeCheck(ResourceHandle* job, void* ptr, size_t totalSize)
{
    ResourceHandleInternal* d = job->getInternal();
    if ((!d->m_response.mimeTypeChecked())) {
        /* in HTTP d->m_mightDownloadFromHandle defualt false;
         * detach the request from the browser or plugins.
         * the request not form plugin
         */
        if (d->client() && (!d->client()->isPluginRequest())) {
            if (!downloadAttachment(d->m_response)) {
                if ((!MIMETypeRegistry::isSupportedMIMEType(d->m_response.mimeType()))
#if ENABLE(PLUGIN)
                    && (!PlugInInfoStore::supportsMIMEType(d->m_response.mimeType()))
#endif
                   )
                    d->m_mightDownloadFromHandle = true;

                MIMEType guestMIMEType = MIMEType::guestFromResource(d->m_request.url(), ptr, totalSize);
                MIMEType responseMIMEType = MIMEType(d->m_response.mimeType());
                if (responseMIMEType.category() != guestMIMEType.category()) {
                    if (guestMIMEType.isText()|| guestMIMEType.isImage()) {
                        d->m_response.setMimeType(guestMIMEType.mimeType());
                        d->m_mightDownloadFromHandle = false;
                    } else if (responseMIMEType.mimeType() == "text/plain")
                        d->m_mightDownloadFromHandle = true;
				}
            } else
                d->m_mightDownloadFromHandle = true;
        }

        d->m_response.setMIMETypeChecked(true);
    }
}

// called with data after all headers have been processed via headerCallback
static size_t httpWriteCallback(void* ptr, size_t size, size_t nmemb, void* data)
{
    ResourceHandle* job = static_cast<ResourceHandle*>(data);
    ResourceHandleInternal* d = job->getInternal();
    if (d->m_cancelled)
        return 0;

    size_t totalSize = size * nmemb;

    // this shouldn't be necessary but apparently is. CURL writes the data
    // of html page even if it is a redirect that was handled internally
    // can be observed e.g. on gmail.com
    CURL* h = d->m_handle;
    long httpCode = 0;
    CURLcode err = curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &httpCode);

	responseMIMETypeCheck(job, ptr, totalSize);

#if ENABLE(NATIVEERROR)
    if (CURLE_OK == err && isAuthentication(httpCode)) {
        if(d->m_authenticate) 
            return totalSize;
        else
            return -1;
    } else if (CURLE_OK == err && httpCode >= 300) 
        return -1;
#else
    if (CURLE_OK == err) {
        if ((isAuthentication(httpCode) && d->m_authenticate) || isServerRedirection(httpCode))
            return totalSize;
    }
#endif

    if (d->needsDownloadClient())
        d->createDownloadClient();

    if (!d->m_response.responseFired())
        d->fireResponse(job);

    if (d->m_cancelled) // Note: m_cancelled will set true in fireResponse.
        return 0;

    if (d->client()) {
        d->client()->didReceiveData(job, static_cast<char*>(ptr), totalSize, 0);
#if ENABLE(HTTPCACHE)
		if (d->m_cacheEntry.isValid())
			d->m_cacheEntry.putData(static_cast<unsigned char*>(ptr), totalSize);
#endif
	}
    return totalSize;
}

static void setupPUT(ResourceHandle*)
{
    notImplemented();
}

static void setupPOST(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
    curl_easy_setopt(d->m_handle, CURLOPT_POST, TRUE);

    String contentType = job->request().httpContentType();
    if (contentType.contains("multipart/form-data", false)) {
        size_t formSize = job->request().httpBody()->size();
        if (formSize) {
            d->m_formElement = 0;
            d->m_readedFormSize = 0;
			d->m_customHeaders = curl_slist_append(d->m_customHeaders, "Expect:");
			curl_easy_setopt(d->m_handle, CURLOPT_HTTPHEADER, d->m_customHeaders);
            curl_easy_setopt(d->m_handle, CURLOPT_READFUNCTION, readCallback);
            curl_easy_setopt(d->m_handle, CURLOPT_READDATA, job);
            curl_easy_setopt(d->m_handle, CURLOPT_POSTFIELDSIZE, formSize);
        }
    }
    else {
        FormData *formData = job->request().httpBody();
        if (formData)
            formData->flatten(d->m_postBytes);
        curl_easy_setopt(d->m_handle, CURLOPT_POSTFIELDSIZE, d->m_postBytes.size());
        if (d->m_postBytes.size() != 0) {
            d->m_customHeaders = curl_slist_append(d->m_customHeaders, "Expect:");
            curl_easy_setopt(d->m_handle, CURLOPT_HTTPHEADER, d->m_customHeaders);
            curl_easy_setopt(d->m_handle, CURLOPT_POSTFIELDS, d->m_postBytes.data());
        }
    }
}

void initHttpJob(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
    KURL kurl = job->request().url();

	initJobEntry(kurl, job);

    curl_easy_setopt(d->m_handle, CURLOPT_PRIVATE, job);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEFUNCTION, httpWriteCallback);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEDATA, job);
    curl_easy_setopt(d->m_handle, CURLOPT_HEADERFUNCTION, httpHeaderCallback);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEHEADER, job);
    curl_easy_setopt(d->m_handle, CURLOPT_AUTOREFERER, 1);
    curl_easy_setopt(d->m_handle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(d->m_handle, CURLOPT_MAXREDIRS, 10);

    if (! d->m_authPwd.isNull()) {
        curl_easy_setopt(d->m_handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(d->m_handle, CURLOPT_USERPWD, d->m_authPwd.data());
    }
    // enable gzip and deflate through Accept-Encoding:
    curl_easy_setopt(d->m_handle, CURLOPT_ENCODING, "");
    curl_easy_setopt(d->m_handle, CURLOPT_COOKIESESSION, true);
    if (cookiesEnabled()) {
        String strCookie = cookies(kurl);
        if (!strCookie.isEmpty()) {
            if (d->m_cookie)
                fastFree(d->m_cookie);
            d->m_cookie = (char*)fastStrdup(strCookie.latin1().data());
            curl_easy_setopt(d->m_handle, CURLOPT_COOKIE, d->m_cookie);
        }
    }

    // url must remain valid through the request
    ASSERT(!d->m_url);
    if (kurl.hasRef())
        d->m_url = (char*)fastStrdup(kurl.ignoreRefURL().utf8().data());
    else
        d->m_url = (char*)fastStrdup(kurl.url().utf8().data());
    curl_easy_setopt(d->m_handle, CURLOPT_URL, d->m_url);

    if (job->request().httpHeaderFields().size() > 0) {
        struct curl_slist* headers = 0;
        HTTPHeaderMap customHeaders = job->request().httpHeaderFields();
        HTTPHeaderMap::const_iterator end = customHeaders.end();
        for (HTTPHeaderMap::const_iterator it = customHeaders.begin(); it != end; ++it) {
            String key = it->first;
            String value = it->second;
            String headerString(key);
            headerString.append(": ");
            headerString.append(value);
            CString headerLatin1 = headerString.latin1();
            headers = curl_slist_append(headers, headerLatin1.data());
        }
        curl_easy_setopt(d->m_handle, CURLOPT_HTTPHEADER, headers);
        d->m_customHeaders = headers;
    }

    if ("GET" == job->request().httpMethod())
        curl_easy_setopt(d->m_handle, CURLOPT_HTTPGET, TRUE);
    else if ("POST" == job->request().httpMethod())
        setupPOST(job);
    else if ("PUT" == job->request().httpMethod())
        setupPUT(job);
    else if ("HEAD" == job->request().httpMethod())
        curl_easy_setopt(d->m_handle, CURLOPT_NOBODY, TRUE);
}

} /* namespace WebCore */
