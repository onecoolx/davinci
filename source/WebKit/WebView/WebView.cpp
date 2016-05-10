/*
 * WebView.cpp: WebView implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "mconfig.h"

#include "WebCommon.h"
#include "WebObject.h"
#include "WebData.h"
#include "WebEvent.h"
#include "WebPoint.h"
#include "WebSize.h"
#include "WebRect.h"
#include "WebString.h"
#include "WebUrl.h"
#include "WebMouseEvent.h"
#include "WebTouchEvent.h"
#include "WebKeyboardEvent.h"
#include "WebView.h"

namespace davinci {

class WebViewImpl
{
public:
    WebViewImpl(WebViewClient& c, const WebSize& s)
        : client(c)
        , size(s)
    {
    }

    WebViewClient& client;
    WebSize size;
};

// WebView
WebView::WebView(WebViewClient& client, const WebSize& size)
    : m_impl(new WebViewImpl(client, size))
{
}

WebView::~WebView()
{
    delete m_impl;
}


WebViewClient& WebView::client(void) const
{
    return m_impl->client;
}

void WebView::loadUrl(const WebUrl& url)
{
}

void WebView::loadUrl(const char* url)
{
}

void WebView::stop(void)
{
}

void WebView::reload(void)
{
}

void WebView::forward(void)
{
}

void WebView::backward(void)
{
}

void WebView::paint(const WebRect& rect)
{
}

void WebView::resize(const WebSize& size)
{
}

void WebView::setContentsPosition(const WebPoint& pos)
{
}

WebPoint WebView::contentsPosition(void) const
{
    return WebPoint();
}

bool WebView::handleMouseEvent(const WebMouseEvent& event)
{
    return false;
}

bool WebView::handleKeyboardEvent(const WebKeyboardEvent& event)
{
    return false;
}

bool WebView::handleTouchEvent(const WebTouchEvent& event)
{
    return false;
}

bool WebView::handleTextInput(unsigned int inputChar, const char* encoding)
{
    return false;
}

bool WebView::handleTextInput(const WebString& text)
{
    return false;
}

void WebView::setFocus(void)
{
}

void WebView::killFocus(void)
{
}

}
