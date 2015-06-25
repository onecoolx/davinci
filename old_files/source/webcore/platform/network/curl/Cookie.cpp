#include "config.h"
#include "Cookie.h"
#include "CString.h"
#include <curl/curl.h>

#if ENABLE(COOKIES)

namespace WebCore {

Cookie::Cookie()
    : m_accessCount(1)
    , m_next(NULL)
    , m_prev(NULL)
    , m_expiry(0)
    , m_isSecure(false)
    , m_isHttpOnly(false)
    , m_isDomain(false)
{
}

Cookie::~Cookie()
{
    if (m_next)
        m_next->m_prev = m_prev;
    if (m_prev)
        m_prev->m_next = m_next;
}

bool Cookie::isExpired()
{
    time_t ct;

    time(&ct);
    if (m_expiry == (time_t)0 || ((m_expiry != (time_t)-1) && (difftime(m_expiry, ct) > 0)))
        return false;
    return true;
}

void Cookie::parse(String &cookie, String &domain)
{
    int  pos=0;	
	bool flag = true;
	bool maxAge = false;
    bool setValue = false;
    String key,value;

    bool equalIsFound = (!cookie.contains("="));
    if (equalIsFound) {
        m_value = cookie;
        return;
    }

    m_expiry = 0;
	pos = cookie.find("Secure", 0, false);
	if (pos == -1) {
		m_isSecure = false;
    }
	else {
		// remove secure value
		cookie.replace(pos-1, 8, "");
        m_isSecure = true;
	}

    while (flag) {
		if (! parse(cookie, key, value)) {
			flag = false;
        }
		else {
			if (equalIgnoringCase(key, "Path")) {
				m_path = value.copy();
            }
			else if (equalIgnoringCase(key, "Max-Age")) {
                time_t now = time(NULL) + value.toInt(); 
                m_expiry = now;
                maxAge = true;
            }
            else if (equalIgnoringCase(key, "Expires")) {
			    /* "Max-Age" precedence in "Expires" */
                if (! maxAge)
                    expireDate(value);
                else
                    continue;
            }
			else if (equalIgnoringCase(key, "Domain")) {
                domain = value;
                m_isDomain = true;
            }
			else if (equalIgnoringCase(key, "Version")) {
                continue;
            }
			else if (equalIgnoringCase(key, "Comment")) {
                continue;
            }
            else {
                /* get name and value */
				if (! setValue) {
                    m_name = key;
				    m_value = value;
                    setValue = true;
                }else
                    continue;
			}
		} 
	}
}

bool Cookie::parse(String &cookie, String &key, String &value)
{
	int pos_key, pos_value;

    /* get key */
    pos_key = cookie.find('=');	
	if (pos_key != -1)
		key = cookie.left(pos_key);
	else
		return false;

	/* get value */
	pos_value = cookie.find(';');
	if (pos_value != -1) {
		value = cookie.substring(pos_key+1, (pos_value-pos_key-1));
		cookie = cookie.substring(pos_value+1, (cookie.length()-pos_value-1) );
	}
	else
        value = cookie = cookie.substring(pos_key+1, (cookie.length()-pos_key-1) ); 
 
    if (value.endsWith("\r\n"))
	    value = value.left(value.length()-2);

    /* trim blank space characters. */
    value = value.stripWhiteSpace();
    key = key.stripWhiteSpace();
    return true;
}

bool Cookie::expireDate(String &cookie)
{
    m_expiry = 0;
    char* gmt = (char*)fastStrdup(cookie.latin1().data());
    time_t tm = curl_getdate(gmt, NULL);
    fastFree(gmt);

    m_expiry = tm;

    if (tm == (time_t)-1)
        return false;
    return true;
}

inline bool operator<(Cookie &a, Cookie &b)
{
    return a.accessCount() < b.accessCount();
}
} /* namespace WebCore */

#endif /* ENABLE(COOKIES) */
