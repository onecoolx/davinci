
#include "config.h"

#ifndef CookieArchiver_h
#define CookieArchiver_h

#if ENABLE(FILECOOKIE)
#include "CString.h"
#include "FileSystem.h"

namespace WebCore {

class Cookie;
class CookieManager;
class DomainCookie;

class CookieArchiver {
public:
    CookieArchiver();
    ~CookieArchiver();

    int load(CookieManager* mgr);
    int save(DomainCookie* domain);
    bool save(CookieManager* mgr);
    void deleteDomain(DomainCookie* domain);

    bool setCookieDir(const String& path);

protected:    
    bool serialize(Cookie* cookie, HFile fp);
    int loadDomain(DomainCookie* domain);

private:
    String m_cookieDir;
};

} /* namespace WebCore */

#endif /* ENABLE(FILECOOKIE) */
#endif /* CookieArchiver_h */
