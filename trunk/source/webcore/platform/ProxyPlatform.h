
#ifndef ProxyPlat_h
#define ProxyPlat_h
#include "CString.h"

namespace WebCore {
class KURL;

struct ProxyItem{
    ProxyItem(char *user, char *pwd, char *host, char *port, int type);
    ProxyItem();
    CString m_user;
    CString m_password;
    CString m_host;
    CString m_port;
    int     m_type;
};

const ProxyItem &proxy(KURL &url);
void  setProxy(ProxyItem &proxy);

bool proxyEnabled();
void setProxyEnabled(bool status);
}
#endif
