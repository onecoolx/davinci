#include "config.h"
#include "ResourceHandle.h"
#include "ResourceHandleInternal.h"
#include "ResourceResponse.h"
#include "ResourceError.h"
#include "ResourceHandleClient.h"
#include "DownloadResourceClient.h"

#include "WebCallback.h"
using namespace MaCross;
namespace WebCore {

DownloadResourceClient::DownloadResourceClient(bool from)
{
}

DownloadResourceClient::~DownloadResourceClient()
{
}

void DownloadResourceClient::cancel(ResourceHandle *job)
{
    ResourceHandleInternal* d = job->getInternal();
    d->m_mightDownloadFromHandle = false;
    job->cancel();
    destroy(job);
}

void DownloadResourceClient::destroy(ResourceHandle *job)
{
    ResourceHandleInternal* d = job->getInternal();
    d->m_mightDownloadFromHandle = false;

    if (d->m_hasDownloadClient) {
        delete this;
		d->m_client = 0;
	}
}

void  DownloadResourceClient::didReceiveResponse(ResourceHandle* job, const ResourceResponse&)
{
}

void  DownloadResourceClient::didReceiveData(ResourceHandle* job, const char* ptr, int length, int lengthReceived)
{
    int result = 0;
    ResourceHandleInternal* d = job->getInternal();
    if (cb_write_file_data) 
        result = cb_write_file_data((int)d->m_handle, job->request().url().url().utf8().data(), 
												ptr, length, d->m_response.expectedContentLength());
    if (!result)
        cancel(job);
}

void  DownloadResourceClient::didFinishLoading(ResourceHandle* job)
{
    ResourceHandleInternal* d = job->getInternal();
    
    if (cb_write_file_data)
        cb_write_file_data((int)d->m_handle, job->request().url().url().utf8().data(), 
						0, d->m_response.expectedContentLength(), d->m_response.expectedContentLength());

    destroy(job);
}

void  DownloadResourceClient::didFail(ResourceHandle* job, const ResourceError&)
{
    didFinishLoading(job);
}

}
