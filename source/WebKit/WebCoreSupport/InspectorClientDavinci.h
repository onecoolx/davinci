/*
 * InspectorClientDavinci.h: InspectorClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef InspectorClientDavinci_h
#define InspectorClientDavinci_h

#include "InspectorClient.h"
#include "InspectorFrontendChannel.h"

class WebView;

namespace WebKit {

class InspectorClientDavinci : public WebCore::InspectorClient, public WebCore::InspectorFrontendChannel {
public:
    explicit InspectorClientDavinci(WebView*);
    ~InspectorClientDavinci();

    virtual void inspectorDestroyed();

    virtual WebCore::InspectorFrontendChannel* openInspectorFrontend(WebCore::InspectorController*);
    virtual void closeInspectorFrontend();
    virtual void bringFrontendToFront();

    virtual void highlight();
    virtual void hideHighlight();

    virtual void populateSetting(const WTF::String& key, WTF::String* value);
    virtual void storeSetting(const WTF::String& key, const WTF::String& value);

    virtual bool sendMessageToFrontend(const WTF::String&);

    void releaseFrontendPage();

private:
    WebView* m_inspectedWebView;
};

} // namespace WebKit

#endif // InspectorClientDavinci_h
