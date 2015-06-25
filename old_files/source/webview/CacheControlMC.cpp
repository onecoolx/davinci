
#include "config.h"
#include "CacheControl.h"

#include "CacheManager.h"


namespace WebCore {

#if ENABLE(HTTPCACHE)

bool cacheEnabled()
{
	return CacheManager::sharedInstance()->cacheEnabled();
}

void setCacheEnabled(bool enable)
{
	CacheManager::sharedInstance()->setCacheEnabled(enable);
}

#else
bool cacheEnabled()
{
	return false;
}

void setCacheEnabled(bool enable)
{
}

#endif

}
