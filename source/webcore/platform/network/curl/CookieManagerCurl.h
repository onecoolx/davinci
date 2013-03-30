
#ifndef CookieManagerCurl_h 
#define CookieManagerCurl_h 

#include "config.h"

#if ENABLE(COOKIES)

#if USE(MULTIPLE_THREADS)
#include <pthread.h>
#endif

#include <wtf/Vector.h>
#include "KURL.h"
#include "PlatformString.h"
#include "algorithm"
#include "CookieJar.h"
#include "Cookie.h"
#include "CookieArchiver.h"

#define LIMIT_COOKIE 1

namespace WebCore {

#define DEFAULT_DOMAINS  (60)
#define DEFAULT_DOMAINCOOKIES  (32)
#define DEFAULT_COOKIES      (240)
#define DEFAULT_COOKIESIZE   (4*1024)


class DomainCookie {
    friend class CookieManager;
    friend class CookieArchiver;
public:
    DomainCookie(String domain);
    String &domain(){ return m_domain;}
    Cookie *head();
    int add(Cookie *newCookie);
    int accessCount() {return m_accessCount;}
    void remove(Cookie *cookie);
    int removeLRUCookies();
    int cookieCount() {return m_cookies;}

private:
    int incAccessCount() {return m_accessCount++;}
    int m_accessCount; 
    bool m_dirty;    /* the host cookie data is dirty */
    int m_cookies;  /* the number of Cookies */
    Cookie *m_head;
    String m_domain;   /* domain string */
};

/* Note: This class CookieManager only support single instance. */
class CookieManager {
public:
    static CookieManager *sharedInstance();
    bool removeAll(void);

    Vector<DomainCookie*>& domains() {return m_domains;}
    int cookieCount();
    int setCookieCount(int num);

#ifdef LIMIT_COOKIE
    bool addDomain(DomainCookie *domain);
#endif

    bool set(const KURL &url, const KURL &policyURL, const String &m_value);
    String get(const KURL &url);

    void setCookiesEnabled(bool enable);
    bool cookiesEnabled();

#ifdef LIMIT_COOKIE
    void setLimits(int maxCookies, int maxDomainCookies, int maxCookieSize);
    int  getLimits(int *maxCookies, int *maxDomainCookies, int *maxCookieSize);
#endif

protected:
    bool equalCookie(Cookie *oldOne, Cookie* newOne);
    void splitURI(const KURL &kurl, String &host, String &domain, String &path);
    bool matchDomain(const String &domain, const String &host);
    DomainCookie *lookup(const String &domain);
    Cookie *lookup(const DomainCookie *domain, const String &host, const String &path, const String &name);
    String matchedCookies(const KURL& kurl , String &path);
    int addCookie(DomainCookie *domain, Cookie *cookie);
    int removeCookie(const DomainCookie *domain, Cookie *cookie);
#if ENABLE(FILECOOKIE)
    bool setCookieDir(const String& path);
#endif

#ifdef LIMIT_COOKIE    
    int removeCookies(DomainCookie *domain);
    int removeLRUDomains(void);
    int removeLRUCookies(DomainCookie *domain);
#endif

private:
    CookieManager();
    ~CookieManager();

#if USE(MULTIPLE_THREADS)
    void lock() { m_lock->lock();}
    void unlock() { m_lock->unlock();}
#else
    void lock() {}
    void unlock() {}
#endif

    Vector<DomainCookie*> m_domains;
    int  m_cookies;
    bool m_enableCookie;   /* default true */

#if ENABLE(FILECOOKIE)
    CookieArchiver *m_archiver;
#endif

#if USE(MULTIPLE_THREADS)
    Mutex *m_lock;
#endif

#ifdef LIMIT_COOKIE
    int m_maxDomains;
    int m_maxCookies;       /* the maximum number of the cookies */
    int m_maxDomainCookies; /* the maximum number of cookies belong the same host */
    int m_maxCookieSize;    /* the maximum size of a single cookie */
#endif
};

} /* namespace WebCore */

#endif /* ENABLE(COOKIES) */

#endif /* CookieManagerCurl_h  */
