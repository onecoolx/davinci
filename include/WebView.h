/*
 * WebView.h: WebView implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_WEBVIEW_H_
#define _DAVINCI_WEBVIEW_H_

namespace davinci {

/**
 * \defgroup content WebView
 * @{
 */
class WebViewClient
{
};

class WebViewImpl;

class EXPORT_API WebView : public WebObject
{
public:
    WebView(WebViewClient& client, const WebSize& size);
    virtual ~WebView();

    WebViewClient& client(void) const;

    void loadUrl(const WebUrl& url);
    void loadUrl(const char* url);
    void stop(void);
    void reload(void);
    void forward(void);
    void backward(void);

    void paint(const WebRect& rect);
    void resize(const WebSize& size);

    void setContentsPosition(const WebPoint& pos);
    WebPoint contentsPosition(void) const;

    bool handleMouseEvent(const WebMouseEvent& event);
    bool handleKeyboardEvent(const WebKeyboardEvent& event);
    bool handleTouchEvent(const WebTouchEvent& event);
    bool handleContextMenuEvent(const WebContextMenuEvent& event);
    bool handleTextInput(unsigned int inputChar, const char* encoding);
    bool handleTextInput(const WebString& text);

    void setFocus(void);
    void killFocus(void);

    void setTextEncoding(WebEncodingType encoding);
    WebEncodingType textEncoding(void) const;
private:
    DECLARE_NO_COPY_AND_ASSIGN(WebView);
    WebViewImpl* m_impl;
};

/** @} end of content*/
} /* namespace davinci */

#endif /*_DAVINCI_WEBVIEW_H_*/
