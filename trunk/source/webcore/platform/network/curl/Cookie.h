
#ifndef Cookie_h
#define Cookie_h

#include <time.h>
#include "config.h"
#include "PlatformString.h"

#if ENABLE(COOKIES)

namespace WebCore {

class CookieManager;

class Cookie {
    friend class DomainCookie;
    friend class CookieManager;
    friend class CookieArchiver;

public:
    Cookie();
    ~Cookie();
    void parse(String &cookie, String &domain);
    bool isExpired();
    int accessCount() {return m_accessCount; };

protected:
    int incAccessCount(){return m_accessCount++;}
    bool parse(String &cookie, String &key, String &value);
    bool expireDate(String &cookie);
    
private:    
    int m_accessCount;
    Cookie *m_next;
    Cookie *m_prev;
    String m_name;
    String m_path;
    String m_host;
    String m_value; 
    time_t m_expiry;
    bool m_isSecure;
    bool m_isHttpOnly;
    bool m_isDomain;
};

} /* namespace WebCore */

#endif /* ENABLE(COOKIE) */
#endif /* Cookie_h */
