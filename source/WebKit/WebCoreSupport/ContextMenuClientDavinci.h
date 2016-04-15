/*
 * ContextMenuClientDavinci.h: ContextMenuClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef ContextMenuClientDavinci_h
#define ContextMenuClientDavinci_h

#include "ContextMenuClient.h"

class WebView;

namespace WebKit {

class ContextMenuClientDavinci : public WebCore::ContextMenuClient {
public:
    ContextMenuClientDavinci(WebView*);

    virtual void contextMenuDestroyed();

    virtual PassOwnPtr<WebCore::ContextMenu> customizeMenu(PassOwnPtr<WebCore::ContextMenu>);
    virtual void contextMenuItemSelected(WebCore::ContextMenuItem*, const WebCore::ContextMenu*);

    virtual void downloadURL(const WebCore::KURL&);
    virtual void copyImageToClipboard(const WebCore::HitTestResult&);
    virtual void searchWithGoogle(const WebCore::Frame*);
    virtual void lookUpInDictionary(WebCore::Frame*);
    virtual void speak(const WTF::String&);
    virtual void stopSpeaking();
    virtual bool isSpeaking();

private:
    WebView* m_webView;
};

} // namespace WebKit

#endif // ContextMenuClientDavinci_h
