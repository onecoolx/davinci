
#include "config.h"
#include "KURL.h"
#include "ProxyPlatform.h"
#include "CString.h"
#include "curl/curl.h"

namespace WebCore {

//FIXME: support mulit proxy feature.
struct ProxyControler {
    ProxyControler();
    ProxyItem m_proxy;
    bool      m_enable;
};

ProxyControler::ProxyControler()
    : m_enable(false)
{
}

static ProxyControler *proxyCtrl()
{
    static ProxyControler * proxy = new ProxyControler();
    return proxy;
}

ProxyItem::ProxyItem()
    : m_type(-1)
{
}

ProxyItem::ProxyItem(char *user, char *pwd, char *host, char *port, int type)
    : m_user(user)
    , m_password(pwd)
    , m_host(host)
    , m_port(port)
    , m_type(type)
{
}

static ProxyItem nullProxy;
const ProxyItem &proxy(KURL &url)
{
    if (url.isLocalFile())
        return nullProxy;

    return proxyCtrl()->m_proxy;
}

void setProxy(ProxyItem &proxy)
{
    proxyCtrl()->m_proxy = proxy;
    switch (proxy.m_type) {
        case 0:
            proxyCtrl()->m_proxy.m_type = CURLPROXY_HTTP;
            break;
        case 1:
            proxyCtrl()->m_proxy.m_type = CURLPROXY_SOCKS4;
            break;
        case 2:
            proxyCtrl()->m_proxy.m_type = CURLPROXY_SOCKS5;
            break;
    }
}

bool proxyEnabled()
{
	return proxyCtrl()->m_enable;
}

void setProxyEnabled(bool status)
{
	proxyCtrl()->m_enable = status;
}

}
