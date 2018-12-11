/*
 * WebUrl.cpp: WebUrl implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "WebCommon.h"
#include "WebObject.h"
#include "WebData.h"
#include "WebString.h"
#include "WebUrl.h"

#include "KURL.h"

namespace davinci {

class WebUrlImpl : public WebCore::KURL
{
};


WebUrl::WebUrl()
    : m_impl(new WebUrlImpl)
{
}

WebUrl::WebUrl(const char* url)
    : m_impl(static_cast<WebUrlImpl*>(new WebCore::KURL(WebCore::ParsedURLString, url)))
{
}

WebUrl::WebUrl(const UChar* url, unsigned int len)
    : m_impl(static_cast<WebUrlImpl*>(new WebCore::KURL(WebCore::ParsedURLString, String(url, len))))
{
}

WebUrl::WebUrl(const WebString& url)
    : m_impl(static_cast<WebUrlImpl*>(new WebCore::KURL(WebCore::ParsedURLString, String((StringImpl*)url.impl()))))
{
}

WebUrl::WebUrl(const WebUrl& o)
    : m_impl(new WebUrlImpl)
{
    *m_impl = *(o.m_impl);
}

WebUrl& WebUrl::operator=(const WebUrl& o)
{
    if (this == &o)
        return *this;

    *m_impl = *(o.m_impl);
    return *this;
}

WebUrl::~WebUrl()
{
    delete m_impl;
}

bool WebUrl::isEmpty(void) const
{
    return m_impl->isEmpty();
}

bool WebUrl::isValid(void) const
{
    return m_impl->isValid();
}

bool WebUrl::isLocalFile(void) const
{
    return m_impl->isLocalFile();
}

WebUrlImpl* WebUrl::impl(void) const
{
    return m_impl;
}

WebString WebUrl::toString(void) const
{
    return WebString((WebStringImpl*)m_impl->string().impl());
}

WebString WebUrl::protocol(void) const
{
    return WebString((WebStringImpl*)m_impl->protocol().impl());
}

WebString WebUrl::host(void) const
{
    return WebString((WebStringImpl*)m_impl->host().impl());
}

WebString WebUrl::path(void) const
{
    return WebString((WebStringImpl*)m_impl->path().impl());
}

WebString WebUrl::query(void) const
{
    return WebString((WebStringImpl*)m_impl->query().impl());
}

WebString WebUrl::userName(void) const
{
    return WebString((WebStringImpl*)m_impl->user().impl());
}

WebString WebUrl::passWord(void) const
{
    return WebString((WebStringImpl*)m_impl->pass().impl());
}

unsigned int WebUrl::port(void) const
{
    return m_impl->port();
}

WebString WebUrl::fragment(void) const
{
    return WebString((WebStringImpl*)m_impl->fragmentIdentifier().impl());
}

}
