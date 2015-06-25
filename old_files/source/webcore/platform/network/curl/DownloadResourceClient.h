
#ifndef DownloadResourceClient_h
#define DownloadResourceClient_h

#include "ResourceHandleClient.h"

namespace WebCore {

class ResourceHandle;
class ResourceResponse;
class ResourceError;

class DownloadResourceClient : public ResourceHandleClient {
public:

    DownloadResourceClient(bool fromSave=false);
    ~DownloadResourceClient();
    
    void destroy(ResourceHandle *);
    void cancel(ResourceHandle *);

    virtual void didReceiveResponse(ResourceHandle*, const ResourceResponse&);
    virtual void didReceiveData(ResourceHandle*, const char*, int, int lengthReceived);
    virtual void didFinishLoading(ResourceHandle*);
    virtual void didFail(ResourceHandle*, const ResourceError&);

};

}

#endif /* DownloadResourceClient_h */
