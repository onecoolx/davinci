#include "config.h"
#include "NetscapePlugInStreamLoader.h"

#include "DocumentLoader.h"

namespace WebCore {

NetscapePlugInStreamLoader::NetscapePlugInStreamLoader(Frame* frame, NetscapePlugInStreamLoaderClient* client)
    : ResourceLoader(frame, true, true)
    , m_client(client)
{
}

NetscapePlugInStreamLoader::~NetscapePlugInStreamLoader()
{
}

PassRefPtr<NetscapePlugInStreamLoader> NetscapePlugInStreamLoader::create(Frame* frame, NetscapePlugInStreamLoaderClient* client)
{
    return new NetscapePlugInStreamLoader(frame, client);
}

bool NetscapePlugInStreamLoader::isDone() const
{
    return !m_client;
}

void NetscapePlugInStreamLoader::releaseResources()
{
    m_client = 0;
    ResourceLoader::releaseResources();
}

void NetscapePlugInStreamLoader::didReceiveResponse(const ResourceResponse& response)
{
    RefPtr<NetscapePlugInStreamLoader> protect(this);

    m_client->didReceiveResponse(this, response);
    ResourceLoader::didReceiveResponse(response);
}

void NetscapePlugInStreamLoader::didReceiveData(const char* data, int length, long long lengthReceived, bool allAtOnce)
{
    RefPtr<NetscapePlugInStreamLoader> protect(this);

    m_client->didReceiveData(this, data, length);
    
    ResourceLoader::didReceiveData(data, length, lengthReceived, allAtOnce);
}

void NetscapePlugInStreamLoader::didFinishLoading()
{
    RefPtr<NetscapePlugInStreamLoader> protect(this);

    m_documentLoader->removePlugInStreamLoader(this);
    m_client->didFinishLoading(this);
    ResourceLoader::didFinishLoading();
}

void NetscapePlugInStreamLoader::didFail(const ResourceError& error)
{
    RefPtr<NetscapePlugInStreamLoader> protect(this);

    m_documentLoader->removePlugInStreamLoader(this);
    m_client->didFail(this, error);
    ResourceLoader::didFail(error);
}

void NetscapePlugInStreamLoader::didCancel(const ResourceError& error)
{
    RefPtr<NetscapePlugInStreamLoader> protect(this);

    m_documentLoader->removePlugInStreamLoader(this);
    m_client->didFail(this, error);
    ResourceLoader::didCancel(error);
}

}
