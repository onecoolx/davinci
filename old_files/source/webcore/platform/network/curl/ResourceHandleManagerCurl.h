
#ifndef ResourceHandleManagerCurl_h_
#define ResourceHandleManagerCurl_h_

#include "Frame.h"
#include "Timer.h"
#include "ResourceHandleClient.h"
#include <curl/curl.h>
#include "CString.h"
namespace WebCore {

class ResourceHandleManager {
public:
    static ResourceHandleManager* sharedInstance();
    void add(ResourceHandle*);
    void cancel(ResourceHandle*);
    void doAuth(ResourceHandle*);
    void startSyncJob(ResourceHandle*);
#if ENABLE(HTTPCACHE)
	void addCacheLoading(ResourceHandle*);
#endif
	static void releaseAllResourceJobs();
private:
    ResourceHandleManager();
    ~ResourceHandleManager();

	void removeAll();
    void downloadTimerCallback(Timer<ResourceHandleManager>*);
#if ENABLE(HTTPCACHE)
	void cacheTimerCallback(Timer<ResourceHandleManager>*);
#endif
    void removeFromCurl(ResourceHandle*);
    void removeResourceHandle(ResourceHandle *);
#if ENABLE(HTTPCACHE)
	void removeCachedResourceHandle(ResourceHandle *);
#endif
    bool removeScheduledJob(ResourceHandle*);
    void initJob(ResourceHandle*);
    bool startAsyncJob(ResourceHandle*);
    bool startScheduledJobs();

    void passCurlToNewResourceHandle(ResourceHandle *);

    Timer<ResourceHandleManager> m_downloadTimer;
#if ENABLE(HTTPCACHE)
	Timer<ResourceHandleManager> m_cacheReaderTimer;
#endif
    CURLM* m_curlMultiHandle;
    CURLSH* m_curlShareHandle;

    char m_curlErrorBuffer[CURL_ERROR_SIZE];
    Vector<ResourceHandle*> m_resourceHandleList;
#if ENABLE(HTTPCACHE)
    Vector<ResourceHandle*> m_cacheHandleList;
	int m_cachingJobs;
#endif
    int m_runningJobs;
    HashMap<String, CString>m_authJar;
};

}

#endif
