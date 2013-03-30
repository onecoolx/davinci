
#include "config.h"

#include "ResourceHandle.h"

#include "DocLoader.h"
#include "ResourceHandleInternalCurl.h"
#include "ResourceHandleManagerCurl.h"
#include "Debug.h"

namespace WebCore {

class SynchronousLoader : public ResourceHandleClient {
public:
    SynchronousLoader();

    void waitForCompletion(ResourceHandle* job);

    virtual void didReceiveResponse(ResourceHandle*, const ResourceResponse&);
    virtual void didReceiveData(ResourceHandle*, const char*, int, int lengthReceived);
    virtual void didFinishLoading(ResourceHandle*);
    virtual void didFail(ResourceHandle*, const ResourceError&);

    ResourceResponse resourceResponse() const { return m_response; }
    ResourceError resourceError() const { return m_error; }
    Vector<char> data() const { return m_data; }

private:
    ResourceResponse m_response;
    ResourceError m_error;
    Vector<char> m_data;
    bool m_finished;
};

SynchronousLoader::SynchronousLoader()
    : m_finished(false)
{
}

void SynchronousLoader::didReceiveResponse(ResourceHandle*, const ResourceResponse& response)
{
    m_response = response;
}

void SynchronousLoader::didReceiveData(ResourceHandle*, const char* data, int length, int)
{
    m_data.append(data, length);
}

void SynchronousLoader::didFinishLoading(ResourceHandle*)
{
    m_finished = true;
}

void SynchronousLoader::didFail(ResourceHandle*, const ResourceError& error)
{
    m_error = error;
    m_finished = true;
}

void SynchronousLoader::waitForCompletion(ResourceHandle *job)
{
    ResourceHandleManager::sharedInstance()->startSyncJob(job);
}

ResourceHandle::~ResourceHandle()
{
#if ENABLE(HTTPCACHE)
	d->m_cacheEntry.clear();
#endif
}

bool ResourceHandle::start()
{
    ref();
    ResourceHandleManager::sharedInstance()->add(this);
    return true;
}

void ResourceHandle::cancel()
{
    ResourceHandleManager::sharedInstance()->cancel(this);
}

PassRefPtr<SharedBuffer> ResourceHandle::bufferedData()
{
    return 0;
}

bool ResourceHandle::supportsBufferedData()
{
    return false;
}

void ResourceHandle::setDefersLoading(bool defers)
{
    d->m_defersLoading = defers;
}

bool ResourceHandle::willLoadFromCache(ResourceRequest& request)
{
    notImplemented();
    return false;
}

void ResourceHandle::loadResourceSynchronously(const ResourceRequest& request, ResourceError& error, ResourceResponse& response, Vector<char>& data)
{
    SynchronousLoader syncLoader;
    RefPtr<ResourceHandle> newHandle = ResourceHandle::create(request, &syncLoader, true, false, false, false);
    syncLoader.waitForCompletion(newHandle.get());
    error = syncLoader.resourceError();
    data = syncLoader.data();
    response = syncLoader.resourceResponse();
}

bool ResourceHandle::loadsBlocked() 
{
    notImplemented();
    return false;
}

} // namespace WebCore

