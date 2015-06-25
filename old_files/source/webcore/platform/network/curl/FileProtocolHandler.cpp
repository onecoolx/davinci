
#include "config.h"
#include "ResourceHandle.h"
#include "MIMETypePlatform.h"
#include "MIMETypeRegistry.h"
#include "HTTPParsers.h"
#include "ResourceHandle.h"
#include "ResourceHandleClient.h"
#include "ResourceHandleInternalCurl.h"

namespace WebCore {

static size_t fileWriteCallback(void* ptr, size_t size, size_t nmemb, void* data)
{
    size_t length = size * nmemb;
    ResourceHandle* job = static_cast<ResourceHandle*>(data);
    ResourceHandleInternal* d = job->getInternal();
    if (d->m_cancelled)
        return 0;

    if (! d->m_response.mimeTypeChecked()) {
        MIMEType guestMIMEType(MIMETypeRegistry::getMIMETypeForPath(d->m_request.url().url()));
        if (d->m_response.mimeType().isEmpty())
            d->m_response.setMimeType(guestMIMEType.mimeType());
        else {
            MIMEType responseMIMEType = MIMEType(d->m_response.mimeType());
            if ((responseMIMEType.category() != guestMIMEType.category())
                    && (!guestMIMEType.isUnknown()))
                d->m_response.setMimeType(guestMIMEType.mimeType());
        }

        if (MIMETypeRegistry::isSupportedMIMEType(d->m_response.mimeType())
                || d->client()->isPluginRequest()) 
            d->m_mightDownloadFromHandle = false; 
        d->m_response.setMIMETypeChecked(true);
    }

    if (d->needsDownloadClient())
        d->createDownloadClient();

    if (! d->m_response.responseFired())
        d->fireResponse(job);

    if (d->m_cancelled) // Note: m_cancelled will set true in fireResponse.
        return 0;

    if (d->client())
        d->client()->didReceiveData(job, static_cast<char*>(ptr), length, 0);

    return length;
}

void initFileJob(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
    DeprecatedString url = job->request().url().url();

    ASSERT(!d->m_url);
	ASSERT(d->client());

    DeprecatedString query = job->request().url().query();
    // Remove any query part sent to a local file.
    if (!query.isEmpty())
        url = url.left(url.find(query));

    // Determine the MIME type based on the path.
	d->m_mightDownloadFromHandle = false;

	d->m_url = (char*)fastStrdup(url.utf8().data());
    curl_easy_setopt(d->m_handle, CURLOPT_URL, d->m_url);
    curl_easy_setopt(d->m_handle, CURLOPT_PRIVATE, job);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEFUNCTION, fileWriteCallback);
    curl_easy_setopt(d->m_handle, CURLOPT_WRITEDATA, job);
}

} /* namespace WebCore */
