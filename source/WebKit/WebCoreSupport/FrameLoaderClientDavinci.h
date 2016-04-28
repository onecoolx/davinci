/*
 * FrameLoaderClientDavinci.h: FrameLoaderClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef FrameLoaderClientDavinci_h
#define FrameLoaderClientDavinci_h

#include "FrameLoaderClient.h"
#include "PluginView.h"
#include "ResourceResponse.h"

class WebViewCore;

namespace WebKit {

class FrameLoaderClientDavinci : public WebCore::FrameLoaderClient {
public:
    FrameLoaderClientDavinci(WebViewCore*);
    virtual ~FrameLoaderClientDavinci();
    virtual void frameLoaderDestroyed();

    WebViewCore* webView() const { return m_core; }

    virtual bool hasWebView() const;

    virtual void makeRepresentation(WebCore::DocumentLoader*);
    virtual void forceLayout();
    virtual void forceLayoutForNonHTML();

    virtual void setCopiesOnScroll();

    virtual void detachedFromParent2();
    virtual void detachedFromParent3();

    virtual void assignIdentifierToInitialRequest(unsigned long identifier, WebCore::DocumentLoader*, const WebCore::ResourceRequest&);

    virtual void dispatchWillSendRequest(WebCore::DocumentLoader*, unsigned long  identifier, WebCore::ResourceRequest&, const WebCore::ResourceResponse& redirectResponse);
    virtual bool shouldUseCredentialStorage(WebCore::DocumentLoader*, unsigned long identifier);
    virtual void dispatchDidReceiveAuthenticationChallenge(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::AuthenticationChallenge&);
    virtual void dispatchDidCancelAuthenticationChallenge(WebCore::DocumentLoader*, unsigned long  identifier, const WebCore::AuthenticationChallenge&);
    virtual void dispatchDidReceiveResponse(WebCore::DocumentLoader*, unsigned long  identifier, const WebCore::ResourceResponse&);
    virtual void dispatchDidReceiveContentLength(WebCore::DocumentLoader*, unsigned long identifier, int dataLength);
    virtual void dispatchDidFinishLoading(WebCore::DocumentLoader*, unsigned long  identifier);
    virtual void dispatchDidFailLoading(WebCore::DocumentLoader*, unsigned long  identifier, const WebCore::ResourceError&);
    virtual bool dispatchDidLoadResourceFromMemoryCache(WebCore::DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&, int length);

    virtual void dispatchDidHandleOnloadEvents();
    virtual void dispatchDidReceiveServerRedirectForProvisionalLoad();
    virtual void dispatchDidCancelClientRedirect();
    virtual void dispatchWillPerformClientRedirect(const WebCore::KURL&, double, double);
    virtual void dispatchDidChangeLocationWithinPage();
    virtual void dispatchDidPushStateWithinPage();
    virtual void dispatchDidReplaceStateWithinPage();
    virtual void dispatchDidPopStateWithinPage();
    virtual void dispatchWillClose();
    virtual void dispatchDidReceiveIcon();
    virtual void dispatchDidStartProvisionalLoad();
    virtual void dispatchDidReceiveTitle(const WebCore::StringWithDirection&);
    virtual void dispatchDidChangeIcons(WebCore::IconType);
    virtual void dispatchDidCommitLoad();
    virtual void dispatchDidFailProvisionalLoad(const WebCore::ResourceError&);
    virtual void dispatchDidFailLoad(const WebCore::ResourceError&);
    virtual void dispatchDidFinishDocumentLoad();
    virtual void dispatchDidFinishLoad();
    virtual void dispatchDidLayout(WebCore::LayoutMilestones);

    virtual WebCore::Frame* dispatchCreatePage(const WebCore::NavigationAction&);
    virtual void dispatchShow();

    virtual void dispatchDecidePolicyForResponse(WebCore::FramePolicyFunction, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&);
    virtual void dispatchDecidePolicyForNewWindowAction(WebCore::FramePolicyFunction, const WebCore::NavigationAction&, const WebCore::ResourceRequest&, WTF::PassRefPtr<WebCore::FormState>, const WTF::String& frameName);
    virtual void dispatchDecidePolicyForNavigationAction(WebCore::FramePolicyFunction, const WebCore::NavigationAction&, const WebCore::ResourceRequest&, WTF::PassRefPtr<WebCore::FormState>);
    virtual void cancelPolicyCheck();

    virtual void dispatchUnableToImplementPolicy(const WebCore::ResourceError&);

    virtual void dispatchWillSendSubmitEvent(WTF::PassRefPtr<WebCore::FormState>) { }
    virtual void dispatchWillSubmitForm(WebCore::FramePolicyFunction, WTF::PassRefPtr<WebCore::FormState>);

    virtual void revertToProvisionalState(WebCore::DocumentLoader*);
    virtual void setMainDocumentError(WebCore::DocumentLoader*, const WebCore::ResourceError&);

    virtual void postProgressStartedNotification();
    virtual void postProgressEstimateChangedNotification();
    virtual void postProgressFinishedNotification();

    virtual PassRefPtr<WebCore::Frame> createFrame(const WebCore::KURL& url, const WTF::String& name, WebCore::HTMLFrameOwnerElement* ownerElement,
                               const WTF::String& referrer, bool allowsScrolling, int marginWidth, int marginHeight);
    virtual PassRefPtr<WebCore::Widget> createPlugin(const WebCore::IntSize&, WebCore::HTMLPlugInElement*, const WebCore::KURL&, const WTF::Vector<WTF::String>&, const WTF::Vector<WTF::String>&, const WTF::String&, bool);
    virtual void recreatePlugin(WebCore::Widget*) { }
    virtual void redirectDataToPlugin(WebCore::Widget* pluginWidget);
    virtual PassRefPtr<WebCore::Widget> createJavaAppletWidget(const WebCore::IntSize&, WebCore::HTMLAppletElement*, const WebCore::KURL& baseURL, const WTF::Vector<WTF::String>& paramNames, const WTF::Vector<WTF::String>& paramValues);
    virtual WTF::String overrideMediaType() const;
    virtual void dispatchDidClearWindowObjectInWorld(WebCore::DOMWrapperWorld*);
    virtual void documentElementAvailable();
    virtual void didPerformFirstNavigation() const;

    virtual void registerForIconNotification(bool);

    virtual WebCore::ObjectContentType objectContentType(const WebCore::KURL&, const WTF::String& mimeType, bool shouldPreferPlugInsForImages);

    virtual void setMainFrameDocumentReady(bool);

    virtual void startDownload(const WebCore::ResourceRequest&, const String& suggestedName = String());

    virtual void willChangeTitle(WebCore::DocumentLoader*);
    virtual void didChangeTitle(WebCore::DocumentLoader*);

    virtual void committedLoad(WebCore::DocumentLoader*, const char*, int);
    virtual void finishedLoading(WebCore::DocumentLoader*);

    virtual void updateGlobalHistory();
    virtual void updateGlobalHistoryRedirectLinks();
    virtual bool shouldGoToHistoryItem(WebCore::HistoryItem*) const;
    virtual bool shouldStopLoadingForHistoryItem(WebCore::HistoryItem*) const;

    virtual void didDisplayInsecureContent();
    virtual void didRunInsecureContent(WebCore::SecurityOrigin*, const WebCore::KURL&);
    virtual void didDetectXSS(const WebCore::KURL&, bool didBlockEntirePage);

    virtual WebCore::ResourceError cancelledError(const WebCore::ResourceRequest&);
    virtual WebCore::ResourceError blockedError(const WebCore::ResourceRequest&);
    virtual WebCore::ResourceError cannotShowURLError(const WebCore::ResourceRequest&);
    virtual WebCore::ResourceError interruptedForPolicyChangeError(const WebCore::ResourceRequest&);

    virtual WebCore::ResourceError cannotShowMIMETypeError(const WebCore::ResourceResponse&);
    virtual WebCore::ResourceError fileDoesNotExistError(const WebCore::ResourceResponse&);
    virtual WebCore::ResourceError pluginWillHandleLoadError(const WebCore::ResourceResponse&);

    virtual bool shouldFallBack(const WebCore::ResourceError&);

    virtual bool canHandleRequest(const WebCore::ResourceRequest&) const;
    virtual bool canShowMIMEType(const WTF::String&) const;
    virtual bool canShowMIMETypeAsHTML(const WTF::String&) const;
    virtual bool representationExistsForURLScheme(const WTF::String&) const;
    virtual WTF::String generatedMIMETypeForURLScheme(const WTF::String&) const;

    virtual void frameLoadCompleted();
    virtual void saveViewStateToItem(WebCore::HistoryItem*);
    virtual void restoreViewState();
    virtual void provisionalLoadStarted();
    virtual void didFinishLoad();
    virtual void prepareForDataSourceReplacement();

    virtual WTF::PassRefPtr<WebCore::DocumentLoader> createDocumentLoader(const WebCore::ResourceRequest&, const WebCore::SubstituteData&);
    virtual void setTitle(const WebCore::StringWithDirection&, const WebCore::KURL&);

    virtual WTF::String userAgent(const WebCore::KURL&);

    virtual void savePlatformDataToCachedFrame(WebCore::CachedFrame*);
    virtual void transitionToCommittedFromCachedFrame(WebCore::CachedFrame*);
    virtual void transitionToCommittedForNewPage();

    virtual void didSaveToPageCache();
    virtual void didRestoreFromPageCache();

    virtual void dispatchDidBecomeFrameset(bool);

    virtual bool canCachePage() const;
    virtual void convertMainResourceLoadToDownload(WebCore::DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&);

    virtual PassRefPtr<WebCore::FrameNetworkingContext> createNetworkingContext();

    void setFrame(WebCore::Frame *frame) { m_frame = frame; }
    WebCore::Frame *frame() { return m_frame; }

private:
    WebViewCore* m_core;
    WebCore::Frame* m_frame;
    WebCore::ResourceResponse m_response;

    // Plugin view to redirect data to
    WebCore::PluginView* m_pluginView;
    bool m_hasSentResponseToPlugin;
};

} // namespace WebKit

#endif // FrameLoaderClientDavinci_h
