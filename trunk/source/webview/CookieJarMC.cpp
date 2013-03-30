
#include "config.h"
#include "CookieJar.h"

#include "CookieManager.h"
#include "PlatformString.h"

namespace WebCore {

#if ENABLE(COOKIES)
void setCookies(const KURL& url, const KURL& policyURL, const String& m_value)
{
    CookieManager::sharedInstance()->set(url, policyURL, m_value);
}

String cookies(const KURL& url)
{
    return CookieManager::sharedInstance()->get(url);
}

bool cookiesEnabled()
{
    return CookieManager::sharedInstance()->cookiesEnabled();
}

void setCookiesEnabled(bool enable)
{
   CookieManager::sharedInstance()->setCookiesEnabled(enable);
}

#else

void setCookies(const KURL& url, const KURL& policyURL, const String& m_value)
{
    return;
}

String cookies(const KURL& url)
{
    return String();
}

bool cookiesEnabled()
{
    return false;
}

void setCookiesEnabled(bool enable)
{
}

#endif /* ENABLE(COOKIES) */

} /* namespace webcore */

