
#include "config.h"
#include <wtf/StringExtras.h>
#include "ASCIICType.h"
#include "ResourceHandle.h"
#include "MIMETypePlatform.h"
#include "MIMETypeRegistry.h"
#include "HTTPParsers.h"
#include "ResourceHandleClient.h"
#include "ResourceHandleInternalCurl.h"

namespace WebCore {


static size_t ftpWriteCallback(char* ptr, size_t size, size_t nmemb, void *data)
{
    size_t length = size * nmemb;
    ResourceHandle* job = static_cast<ResourceHandle*>(data);
    ResourceHandleInternal* d = job->getInternal();
    if (d->m_cancelled)
        return 0;

    // in FTP d->m_mightDownloadFromHandle defualt true;
    if (! d->m_response.mimeTypeChecked()) {
        MIMEType guestMIMEType = MIMEType::guestFromResource(d->m_request.url(), ptr, length);
        MIMEType responseMIMEType = MIMEType(d->m_response.mimeType());
        if ((responseMIMEType.category() != guestMIMEType.category()) && (!guestMIMEType.isUnknown()))
            d->m_response.setMimeType(guestMIMEType.mimeType());

        if (MIMETypeRegistry::isSupportedMIMEType(d->m_response.mimeType())
                || d->client()->isPluginRequest()) 
            d->m_mightDownloadFromHandle = false;
        d->m_response.setMIMETypeChecked(true);
    }

    if (d->needsDownloadClient())
        d->createDownloadClient();

    if (!d->m_response.responseFired())
        d->fireResponse(job);

    if (d->client())
        d->client()->didReceiveData(job, static_cast<char*>(ptr), length, 0);

    return length;
}

static size_t ftpHeaderCallback(char* ptr, size_t size, size_t nmemb, void* data)
{
    int i=0;
    int len = size * nmemb;

    while (i < len) {
        if (ptr[i] == ' ')
            break;
        ++i;
    }

    if (i == len)
        return len;

    ResourceHandle* job = static_cast<ResourceHandle*>(data);
    ResourceHandleInternal* d = job->getInternal();
    if (d->m_cancelled)
        return 0;
    
    d->m_mightDownloadFromHandle = true;

    int resCode = atol(ptr);
    switch (resCode) {
    case 213:
        d->m_response.setExpectedContentLength(atoll(ptr+i+1));
        break;
#if ENABLE(FTPDIR)
    case 150:
        if (d->m_request.url().path() == "" || d->m_request.url().path().endsWith("/")) {
            d->m_response.setMimeType("application/x-ftp-directory");
            d->m_mightDownloadFromHandle = false;
        }
        break;
#endif
    default:
        break;
    }
    return len;
}

void initFtpJob(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
    DeprecatedString url = job->request().url().url();

    ASSERT(!d->m_url);
    d->m_url = (char*)fastStrdup(url.utf8().data());
    curl_easy_setopt(d->m_handle, CURLOPT_URL, d->m_url);
    curl_easy_setopt(d->m_handle, CURLOPT_PRIVATE, job);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEFUNCTION, ftpWriteCallback);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEDATA, job);
    curl_easy_setopt(d->m_handle, CURLOPT_HEADERFUNCTION, ftpHeaderCallback);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEHEADER, job);
}

} /* namespace WebCore */
