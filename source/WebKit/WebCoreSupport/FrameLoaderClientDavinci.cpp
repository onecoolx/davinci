/*
 * FrameLoaderClientDavinci.cpp: FrameLoaderClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "FrameLoaderClientDavinci.h"

#include "DocumentLoader.h"
#include "FrameLoader.h"
#include "FrameNetworkingContextDavinci.h"
#include "FrameView.h"
#include "HTMLFormElement.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PluginDatabase.h"
#include "PolicyChecker.h"
#include "RenderPart.h"
#include "SystemInfo.h"
#include "WebKitVersion.h"
#include "WebView.h"
#include <wtf/text/StringConcatenate.h>

using namespace WebCore;

namespace WebKit {

FrameLoaderClientDavinci::FrameLoaderClientDavinci(WebView* view)
    : m_webView(view)
    , m_pluginView(0)
{
    ASSERT(m_webView);
}

FrameLoaderClientDavinci::~FrameLoaderClientDavinci()
{
}

String FrameLoaderClientDavinci::userAgent(const KURL&)
{
    DEFINE_STATIC_LOCAL(String, userAgentString, ());

    if (userAgentString.isNull()) {
        String webKitVersion = String::format("%d.%d", WEBKIT_MAJOR_VERSION, WEBKIT_MINOR_VERSION);
        userAgentString = makeString("Mozilla/5.0 (", windowsVersionForUAString(), ") AppleWebKit/", webKitVersion, " (KHTML, like Gecko) Mobile Safari/", webKitVersion);
    }

    return userAgentString;
}

PassRefPtr<DocumentLoader> FrameLoaderClientDavinci::createDocumentLoader(const WebCore::ResourceRequest& request, const SubstituteData& substituteData)
{
    return DocumentLoader::create(request, substituteData);
}

void FrameLoaderClientDavinci::committedLoad(DocumentLoader* loader, const char* data, int length)
{
    if (m_pluginView) {
        if (!m_hasSentResponseToPlugin) {
            m_pluginView->didReceiveResponse(loader->response());
            m_hasSentResponseToPlugin = true;
        }
        m_pluginView->didReceiveData(data, length);
    } else
        loader->commitData(data, length);
}

bool FrameLoaderClientDavinci::shouldUseCredentialStorage(DocumentLoader*, unsigned long)
{
    notImplemented();
    return false;
}

void FrameLoaderClientDavinci::dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchWillSendRequest(DocumentLoader*, unsigned long, WebCore::ResourceRequest&, const WebCore::ResourceResponse&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::assignIdentifierToInitialRequest(unsigned long, DocumentLoader*, const WebCore::ResourceRequest&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::postProgressStartedNotification()
{
    notImplemented();
}

void FrameLoaderClientDavinci::postProgressEstimateChangedNotification()
{
    notImplemented();
}

void FrameLoaderClientDavinci::postProgressFinishedNotification()
{
    notImplemented();
}

void FrameLoaderClientDavinci::frameLoaderDestroyed()
{
    m_webView = 0;
    m_frame = 0;
    delete this;
}

void FrameLoaderClientDavinci::dispatchDidReceiveResponse(DocumentLoader*, unsigned long, const ResourceResponse& response)
{
    m_response = response;
}

void FrameLoaderClientDavinci::dispatchDecidePolicyForResponse(FramePolicyFunction policyFunction, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest&)
{
    if (canShowMIMEType(response.mimeType()))
        (m_frame->loader().policyChecker()->*policyFunction)(PolicyUse);
    else
        (m_frame->loader().policyChecker()->*policyFunction)(PolicyDownload);
}

void FrameLoaderClientDavinci::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction policyFunction, const NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<FormState>, const String&)
{
    (m_frame->loader().policyChecker()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientDavinci::dispatchDecidePolicyForNavigationAction(FramePolicyFunction policyFunction, const NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<FormState>)
{
    (m_frame->loader().policyChecker()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientDavinci::dispatchWillSubmitForm(FramePolicyFunction policyFunction, PassRefPtr<FormState>)
{
    (m_frame->loader().policyChecker()->*policyFunction)(PolicyUse);
}

PassRefPtr<Widget> FrameLoaderClientDavinci::createPlugin(const IntSize&, HTMLPlugInElement*, const KURL&, const Vector<String>&, const Vector<String>&, const String&, bool)
{
    return 0;
}

PassRefPtr<Frame> FrameLoaderClientDavinci::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement,
                                                 const String& referrer, bool allowsScrolling, int marginWidth, int marginHeight)
{
#if 0
    return m_webView->createFrame(url, name, ownerElement, referrer, allowsScrolling, marginWidth, marginHeight);
#endif
}

void FrameLoaderClientDavinci::redirectDataToPlugin(Widget* pluginWidget)
{
    m_pluginView = toPluginView(pluginWidget);
    if (pluginWidget)
        m_hasSentResponseToPlugin = false;
}

PassRefPtr<Widget> FrameLoaderClientDavinci::createJavaAppletWidget(const IntSize&, HTMLAppletElement*, const KURL&, const Vector<String>&, const Vector<String>&)
{
    notImplemented();
    return 0;
}

ObjectContentType FrameLoaderClientDavinci::objectContentType(const KURL& url, const String& mimeType, bool shouldPreferPlugInsForImages)
{
    return FrameLoader::defaultObjectContentType(url, mimeType, shouldPreferPlugInsForImages);
}

String FrameLoaderClientDavinci::overrideMediaType() const
{
    notImplemented();
    return String();
}

void FrameLoaderClientDavinci::dispatchDidClearWindowObjectInWorld(DOMWrapperWorld*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::documentElementAvailable()
{
    notImplemented();
}

void FrameLoaderClientDavinci::didPerformFirstNavigation() const
{
    notImplemented();
}

void FrameLoaderClientDavinci::registerForIconNotification(bool)
{
    notImplemented();
}

void FrameLoaderClientDavinci::setMainFrameDocumentReady(bool)
{
    notImplemented();
}

bool FrameLoaderClientDavinci::hasWebView() const
{
    return true;
}

void FrameLoaderClientDavinci::dispatchDidFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientDavinci::frameLoadCompleted()
{
    notImplemented();
}

void FrameLoaderClientDavinci::saveViewStateToItem(HistoryItem*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::restoreViewState()
{
    notImplemented();
}

bool FrameLoaderClientDavinci::shouldGoToHistoryItem(HistoryItem* item) const
{
    return item;
}

bool FrameLoaderClientDavinci::shouldStopLoadingForHistoryItem(HistoryItem* item) const
{
    return true;
}

void FrameLoaderClientDavinci::didDisplayInsecureContent()
{
    notImplemented();
}

void FrameLoaderClientDavinci::didRunInsecureContent(SecurityOrigin*, const KURL&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::didDetectXSS(const KURL&, bool)
{
    notImplemented();
}

void FrameLoaderClientDavinci::makeRepresentation(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::forceLayout()
{
    notImplemented();
}

void FrameLoaderClientDavinci::forceLayoutForNonHTML()
{
    notImplemented();
}

void FrameLoaderClientDavinci::setCopiesOnScroll()
{
    notImplemented();
}

void FrameLoaderClientDavinci::detachedFromParent2()
{
    notImplemented();
}

void FrameLoaderClientDavinci::detachedFromParent3()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidHandleOnloadEvents()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidReceiveServerRedirectForProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidCancelClientRedirect()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchWillPerformClientRedirect(const KURL&, double, double)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidChangeLocationWithinPage()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidPushStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidReplaceStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidPopStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchWillClose()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidReceiveIcon()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidStartProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidReceiveTitle(const StringWithDirection&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidChangeIcons(WebCore::IconType)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidCommitLoad()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidFinishDocumentLoad()
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidLayout(LayoutMilestones)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchShow()
{
    notImplemented();
}

void FrameLoaderClientDavinci::cancelPolicyCheck()
{
    notImplemented();
}

void FrameLoaderClientDavinci::revertToProvisionalState(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::willChangeTitle(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::didChangeTitle(DocumentLoader* documentLoader)
{
    setTitle(documentLoader->title(), documentLoader->url());
}

bool FrameLoaderClientDavinci::canHandleRequest(const WebCore::ResourceRequest&) const
{
    notImplemented();
    return true;
}

bool FrameLoaderClientDavinci::canShowMIMEType(const String& type) const
{
    return (MIMETypeRegistry::canShowMIMEType(type)
            || PluginDatabase::installedPlugins()->isMIMETypeRegistered(type));
}

bool FrameLoaderClientDavinci::canShowMIMETypeAsHTML(const String&) const
{
    notImplemented();
    return false;
}

bool FrameLoaderClientDavinci::representationExistsForURLScheme(const String&) const
{
    notImplemented();
    return false;
}

String FrameLoaderClientDavinci::generatedMIMETypeForURLScheme(const String&) const
{
    notImplemented();
    return String();
}

void FrameLoaderClientDavinci::finishedLoading(DocumentLoader*)
{
    if (!m_pluginView)
        return;

    m_pluginView->didFinishLoading();
    m_pluginView = 0;
    m_hasSentResponseToPlugin = false;
}

void FrameLoaderClientDavinci::provisionalLoadStarted()
{
    notImplemented();
}

void FrameLoaderClientDavinci::didFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientDavinci::prepareForDataSourceReplacement()
{
    notImplemented();
}

void FrameLoaderClientDavinci::setTitle(const StringWithDirection&, const KURL&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidReceiveContentLength(DocumentLoader*, unsigned long, int)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidFinishLoading(DocumentLoader*, unsigned long)
{
    notImplemented();
}

void FrameLoaderClientDavinci::dispatchDidFailLoading(DocumentLoader*, unsigned long, const ResourceError&)
{
    notImplemented();
}

bool FrameLoaderClientDavinci::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&, int)
{
    notImplemented();
    return false;
}

void FrameLoaderClientDavinci::dispatchDidFailProvisionalLoad(const ResourceError& error)
{
    dispatchDidFailLoad(error);
}

void FrameLoaderClientDavinci::dispatchDidFailLoad(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::convertMainResourceLoadToDownload(WebCore::DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&)
{
    notImplemented();
}

ResourceError FrameLoaderClientDavinci::cancelledError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientDavinci::blockedError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientDavinci::cannotShowURLError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientDavinci::interruptedForPolicyChangeError(const WebCore::ResourceRequest&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientDavinci::cannotShowMIMETypeError(const WebCore::ResourceResponse&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientDavinci::fileDoesNotExistError(const WebCore::ResourceResponse&)
{
    return ResourceError();
}

ResourceError FrameLoaderClientDavinci::pluginWillHandleLoadError(const WebCore::ResourceResponse&)
{
    return ResourceError();
}

bool FrameLoaderClientDavinci::shouldFallBack(const ResourceError& error)
{
    return !(error.isCancellation());
}

bool FrameLoaderClientDavinci::canCachePage() const
{
    return true;
}

Frame* FrameLoaderClientDavinci::dispatchCreatePage(const NavigationAction&)
{
    notImplemented();
    return 0;
}

void FrameLoaderClientDavinci::dispatchUnableToImplementPolicy(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientDavinci::setMainDocumentError(DocumentLoader*, const ResourceError& error)
{
    if (!m_pluginView)
        return;

    m_pluginView->didFail(error);
    m_pluginView = 0;
    m_hasSentResponseToPlugin = false;
}

void FrameLoaderClientDavinci::startDownload(const WebCore::ResourceRequest&, const String& /* suggestedName */)
{
    notImplemented();
}

void FrameLoaderClientDavinci::updateGlobalHistory()
{
    notImplemented();
}

void FrameLoaderClientDavinci::updateGlobalHistoryRedirectLinks()
{
    notImplemented();
}

void FrameLoaderClientDavinci::savePlatformDataToCachedFrame(CachedFrame*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::transitionToCommittedFromCachedFrame(CachedFrame*)
{
    notImplemented();
}

void FrameLoaderClientDavinci::transitionToCommittedForNewPage()
{
#if 0
    Page* page = m_frame->page();
    ASSERT(page);

    bool isMainFrame = m_frame == page->mainFrame();

    m_frame->setView(0);

    RefPtr<FrameView> frameView;
    if (isMainFrame) {
        RECT rect;
        m_webView->frameRect(&rect);
        frameView = FrameView::create(m_frame, IntRect(rect).size());
    } else
        frameView = FrameView::create(m_frame);

    m_frame->setView(frameView);

    if (m_frame->ownerRenderer())
        m_frame->ownerRenderer()->setWidget(frameView);
#endif
}

void FrameLoaderClientDavinci::didSaveToPageCache()
{
}

void FrameLoaderClientDavinci::didRestoreFromPageCache()
{
}

void FrameLoaderClientDavinci::dispatchDidBecomeFrameset(bool)
{
}

PassRefPtr<WebCore::FrameNetworkingContext> FrameLoaderClientDavinci::createNetworkingContext()
{
    return FrameNetworkingContextDavinci::create(m_frame, userAgent(KURL()));
}

} // namespace WebKit
