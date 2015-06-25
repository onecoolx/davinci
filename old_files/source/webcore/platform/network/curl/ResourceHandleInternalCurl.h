// -*- mode: c++; c-basic-offset: 4 -*-
/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
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

#ifndef ResourceHandleInternalCurl_h
#define ResourceHandleInternalCurl_h

#include "ResourceRequest.h"
#include "AuthenticationChallenge.h"
#include "DownloadResourceClient.h"
#include <curl/curl.h>
#include "CString.h"

#include "CacheEntry.h"

namespace WebCore {
    
    class ResourceHandleClient;

    class ResourceHandleInternal : Noncopyable {
    public:
        ResourceHandleInternal(ResourceHandle* loader, const ResourceRequest& request, ResourceHandleClient* c, bool defersLoading, bool shouldContentSniff, bool mightDownloadFromHandle, bool asyncDownload)
            : m_client(c)
            , m_request(request)
            , m_asyncDownload(asyncDownload)
            , m_defersLoading(defersLoading)
            , m_shouldContentSniff(shouldContentSniff)
            , m_mightDownloadFromHandle(mightDownloadFromHandle)
            , m_cancelled(false) 
            , m_hasDownloadClient(false) 
            , m_hasCurlHandle(false) 
            , m_forSavingResource(false) 
            , m_authenticate(true)
            , m_handle(0)
            , m_url(0)
            , m_cookie(0)
			, m_proxyHost(0)
            , m_proxyUserPwd(0)
            , m_customHeaders(0)
#if ENABLE(HTTPCACHE)
			, m_cacheReader(false)
#endif
        {
        }
        
        ~ResourceHandleInternal()
        {
            if (m_url) {
                fastFree(m_url);
                m_url = 0;
            }

            if (m_cookie) {
                fastFree(m_cookie);
                m_cookie = 0;
            }

			if (m_proxyHost)
				delete[] m_proxyHost;
            
            if (m_proxyUserPwd)
                delete[] m_proxyUserPwd;
            
            if (m_customHeaders) {
                curl_slist_free_all(m_customHeaders);
                m_customHeaders = 0;
            }
        }

        bool needsDownloadClient() { return m_mightDownloadFromHandle && (!m_hasDownloadClient); }
        void createDownloadClient() {
            m_client = new DownloadResourceClient();
            m_hasDownloadClient = true;
        }

        bool needsResourceHandleForDownloading() {return m_mightDownloadFromHandle && (!m_forSavingResource);}

        void fireResponse(ResourceHandle *job)
        {
            const char* hdr; 
            curl_easy_getinfo(m_handle, CURLINFO_EFFECTIVE_URL, &hdr);
            m_response.setUrl(KURL(hdr));
            if (client())
                client()->didReceiveResponse(job, m_response);
            m_response.setResponseFired(true);
        }

#if ENABLE(HTTPCACHE)
		bool isCacheReader() { return m_cacheReader; }
#endif

        ResourceHandleClient* client() { return m_client; }
        ResourceHandleClient* m_client;

        ResourceRequest m_request;

        bool m_asyncDownload;
        bool m_defersLoading;
        bool m_shouldContentSniff;
        bool m_mightDownloadFromHandle;
        bool m_cancelled;
        bool m_hasDownloadClient;
        bool m_hasCurlHandle;
        bool m_forSavingResource;
        bool m_authenticate;

        CURL *m_handle;
        char *m_url;
        char *m_cookie;
		char *m_proxyHost;
        char *m_proxyUserPwd;
        CString m_authPwd;
        long  m_readedFormSize;
        size_t m_formElement;
        struct curl_slist* m_customHeaders;
        Vector<char> m_postBytes;
        ResourceResponse m_response;
        AuthenticationChallenge m_currentWebChallenge;
#if ENABLE(HTTPCACHE)
		bool m_cacheReader;
		CacheEntry m_cacheEntry;
#endif
    };

} // namespace WebCore

#endif // ResourceHandleInternal_h
