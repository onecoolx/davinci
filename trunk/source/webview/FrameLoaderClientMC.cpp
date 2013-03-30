
#include "config.h"
#include "macross.h"

#include "Frame.h"
#include "FrameView.h"
#include "FrameTree.h"
#include "FrameLoader.h"
#include "CString.h"
#include "FrameLoaderClientMC.h"
#include "PlatformString.h"
#include "ResourceRequest.h"
#include "ResourceError.h"
#include "DocumentLoader.h"
#include "HTMLFrameElement.h"
#include "HTMLGenericFormElement.h"
#include "HTMLInputElement.h"
#include "HTMLFrameOwnerElement.h"
#include "HTMLNames.h"
#include "MIMETypeRegistry.h"
#include "ResourceResponse.h"
#include "Page.h"
#include "ChromeClientMC.h"
#include "ProgressTracker.h"
#include "HistoryItem.h"
#include "LocalizedStrings.h"
#include <wtf/RefPtr.h>
#include "HTTPParsers.h"
#include "Settings.h"
#include "Debug.h"
#include "MIMETypePS.h"
#include "SchemeExtension.h"
#if PLATFORM(UNIX)
#include <sys/utsname.h>
#endif

#if ENABLE(PLUGIN)
#include "HTMLPlugInElement.h" 
#include "PluginViewPS.h"
#include "PluginDatabasePS.h"
#include "PlugInInfoStore.h"
#endif 

#include "WebCallback.h"
#include "WebEngine.h"
#include "WebView.h"

using namespace MaCross;

namespace WebCore {

FrameLoaderClientMC::FrameLoaderClientMC()
    : m_frame(0)
    , m_firstData(false)
{
}

FrameLoaderClientMC::~FrameLoaderClientMC()
{
}

void FrameLoaderClientMC::frameLoaderDestroyed()
{
    m_frame = 0;
    delete this;
}

bool FrameLoaderClientMC::hasWebView() const
{
    return true;
}

bool FrameLoaderClientMC::hasFrameView() const
{
    return true;
}

void FrameLoaderClientMC::dispatchDidReceiveResponse(DocumentLoader* loader, unsigned long identifier, const ResourceResponse& response)
{
    m_response = response;
    m_firstData = true;
    
    if ((!loader->isLoadingSubresources()) && (loader->frame() == m_frame->page()->mainFrame())) {
        if (equalIgnoringCase(loader->request().httpMethod(), "POST"))
            loader->request().setHTTPMethod("GET");
    }

    if (cb_set_status) {
        String status_msg = statusTransferDefaultLabel() + String::fromUTF8(response.url().url().utf8().data());
        cb_set_status(m_frame->view()->containingView(), status_msg.utf8().data());
    }
}

void FrameLoaderClientMC::dispatchDecidePolicyForMIMEType(FramePolicyFunction policyFunction, 
                                                                    const String& MIMEType, const ResourceRequest&)
{
    if (!policyFunction || !m_frame)
        return;
    (m_frame->loader()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientMC::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction policyFunction, const NavigationAction&,
                                                                     const ResourceRequest&, const String& frameName)
{
    if (!policyFunction || !m_frame)
        return;
    (m_frame->loader()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientMC::dispatchDecidePolicyForNavigationAction(FramePolicyFunction policyFunction, const NavigationAction&,
                                                                                                   const ResourceRequest&)
{
    if (!policyFunction || !m_frame)
        return;
    (m_frame->loader()->*policyFunction)(PolicyUse);
}

void FrameLoaderClientMC::dispatchWillSubmitForm(FramePolicyFunction policyFunction, PassRefPtr<FormState> form)
{
    if (!policyFunction || !m_frame)
        return;

	if (cb_save_submit_form) {
		int passCount = 0;
		Vector<HTMLGenericFormElement*> items = form->form()->formElements;
		for (size_t i = 0; i < items.size(); i++) {
			if (items[i]->isPassWordField())
				passCount++;
		}

		if (1 == passCount) {
			// I think it is a login form. save it
			CString base = m_frame->loader()->baseURL().url().utf8();
			CString target = form->form()->action().utf8();
			CString fname = form->form()->name().utf8();
			if (!fname.length())
				fname = form->form()->id().utf8();

			int itemsCount = 0;
			for (size_t i = 0; i < items.size(); i++) {
				if (items[i]->isPassWordField() || items[i]->isTextField()) {
					itemsCount++;
				}
			}
	
			for (size_t i = 0; i < items.size(); i++) {
				if (items[i]->isPassWordField() || items[i]->isTextField()) {
					String iname = items[i]->name().domString();
					if (iname.isEmpty())
						iname = items[i]->id();

					CString name = iname.utf8();
					CString value = reinterpret_cast<HTMLInputElement*>(items[i])->value().utf8();

					itemsCount--;
					if (!cb_save_submit_form(base.data(), fname.data(), target.data(), name.data(), 
												value.data(), itemsCount == 0 ? TRUE : FALSE))
						return;
					/*
					FIXME: menulist, radio and check are not save and auto fill in this version.
					if (items[i]->isRadioButton() || items[i]->isCheckBox()) {
					bool c = reinterpret_cast<HTMLInputElement*>(items[i])->isChecked();
					}
					*/
				}
			}
		}
	}

    (m_frame->loader()->*policyFunction)(PolicyUse);
}

PassRefPtr<DocumentLoader> FrameLoaderClientMC::createDocumentLoader(const ResourceRequest& request, const SubstituteData& substituteData)
{
    RefPtr<DocumentLoader> loader = new DocumentLoader(request, substituteData);
    return loader.release();
}

static String agentOS()
{
#if PLATFORM(UNIX)
    struct utsname name;
    if (uname(&name) != -1)
        return String::format("%s %s", name.sysname, name.machine);
    else
        return "Unknown";
#elif PLATFORM(WINCE)
    return "Windows CE";
#elif PLATFORM(WIN32)
    return "Windows NT";
#else
    return "Unknown";
#endif
}

String composeUserAgent(void)
{
    // This is a liberal interpretation of http://www.mozilla.org/build/revised-user-agent-strings.html
    // See also http://developer.apple.com/internet/safari/faq.html#anchor2
    String ua;

    // Product
    ua += "Mozilla/5.0 ";

    // Comment
    ua += "(MaCross; "; // Platform
    ua += "U; ";  // Security
    ua += agentOS() + "; "; // OS-or-CPU
    ua += defaultLanguage() + ";) "; // Localization information

    ua += "MaCross/";
	ua += VERSION;
    ua += " (Compatible Gecko 1.8, Firefox/1.5.0)";

    return ua;
}

String FrameLoaderClientMC::userAgent(const KURL& url)
{
    static String UA;
	if (UA.isEmpty())
		UA = composeUserAgent();

    if (cb_user_agent_custom) {
		String usa = String(cb_user_agent_custom(url.url().utf8().data()));
		if (!usa.isEmpty() && !usa.isNull())
			return usa;
		else
        	return UA;
    } else {
        return UA;
    }
}

bool FrameLoaderClientMC::canShowMIMEType(const String& MIMEType) const
{
    if (MIMETypeRegistry::isSupportedImageMIMEType(MIMEType))
        return true;

    if (MIMETypeRegistry::isSupportedNonImageMIMEType(MIMEType))
        return true;

#if ENABLE(PLUGIN)
    if (PlugInInfoStore::supportsMIMEType(MIMEType))
        return true;
#endif

    return false;
}

void FrameLoaderClientMC::committedLoad(DocumentLoader* loader, const char* data, int length)
{
    FrameLoader *fl = loader->frameLoader();
    if (m_firstData) {
        String encoding = loader->overrideEncoding();
        bool userChosen = !encoding.isNull();
        if (encoding.isEmpty())
            encoding = loader->response().textEncodingName();
        fl->setEncoding(encoding, userChosen);
        m_firstData = false;
    }

    fl->addData(data, length);
}

void FrameLoaderClientMC::willChangeTitle(DocumentLoader* loader)
{
    // no need for, dispatchDidReceiveTitle is the right callback
}

void FrameLoaderClientMC::dispatchDidSetLocation(const KURL& location)
{
    if (cb_set_location && (m_frame == m_frame->page()->mainFrame())) 
        cb_set_location(m_frame->view()->containingView(), location.url().utf8().data());
}

void FrameLoaderClientMC::dispatchDidReceiveTitle(const String& title)
{
    if (cb_set_title && (m_frame == m_frame->page()->mainFrame()))
        cb_set_title(m_frame->view()->containingView(), title.utf8().data());   
}

void FrameLoaderClientMC::didChangeTitle(DocumentLoader* l)
{
    // no need for, dispatchDidReceiveTitle is the right callback
}

void FrameLoaderClientMC::setTitle(const String& title, const KURL& url)
{
    // no need for, dispatchDidReceiveTitle is the right callback
}

PassRefPtr<Frame> FrameLoaderClientMC::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement,
            const String& referrer, ScrollbarMode modeScrolling, int marginWidth, int marginHeight)
{
    FrameLoaderClientMC *client = new FrameLoaderClientMC;
    Frame* frame = new Frame(m_frame->page(), ownerElement, client);
    client->setFrame(frame);
    FrameView* frameView = new FrameView(frame);
    frame->setView(frameView);
    frameView->setContainingView(m_frame->view()->containingView());
    frameView->deref();
    frame->init();

    RefPtr<Frame> childFrame(adoptRef(frame));

    childFrame->view()->setScrollbarsMode(modeScrolling);
    if (marginWidth != -1)
        childFrame->view()->setMarginWidth(marginWidth);
    if (marginHeight != -1)
        childFrame->view()->setMarginHeight(marginHeight);

    m_frame->tree()->appendChild(childFrame);
    childFrame->tree()->setName(name);
    FrameLoadType childLoadType = FrameLoadTypeRedirectWithLockedHistory;
    childFrame->loader()->load(url, referrer, childLoadType, String(), 0, 0);

    if (!childFrame->tree()->parent())
        return 0;

    return childFrame.release();
}

Widget* FrameLoaderClientMC::createPlugin(const IntSize& pluginSize, Element* ownerElement, const KURL& URL, 
                                            const Vector<String>& paramNames, const Vector<String>& paramValues,
		                                    const String& mimeType, bool loadManually)
{
//#warning need implements
		/*
#if ENABLE(PLUGIN)
	PluginViewMC* pluginView = PluginDatabaseMg::instancePlugins()->createPluginView(m_frame, pluginSize, ownerElement, URL, paramNames, paramValues, mimeType, loadManually);
	if (pluginView && pluginView->status() == PluginStatusLoadedSuccessfully)
		return pluginView;
#endif //ENABLE(PLUGIN)
	return NULL;*/
	return NULL;
}

void FrameLoaderClientMC::forceLayout()
{
    m_frame->view()->setNeedsLayout();
    m_frame->view()->layout();
}

void FrameLoaderClientMC::postProgressStartedNotification()
{
	if (m_frame) { 
		if (cb_loading_progress && m_frame->loader()->isLoadingMainFrame())
			cb_loading_progress(m_frame->view()->containingView(), 0, FALSE);
	}
}

void FrameLoaderClientMC::postProgressEstimateChangedNotification()
{
	if (m_frame && m_frame->page()) {
		unsigned percent = (unsigned)(m_frame->page()->progress()->estimatedProgress()*100);
		if (cb_loading_progress && m_frame->loader()->isLoadingMainFrame()) 
			cb_loading_progress(m_frame->view()->containingView(), percent, FALSE);
	}
}

void FrameLoaderClientMC::postProgressFinishedNotification()
{
	if (m_frame) {
		if (cb_loading_progress && m_frame->loader()->isLoadingMainFrame())
			cb_loading_progress(m_frame->view()->containingView(), 100, TRUE);
	}
}

bool FrameLoaderClientMC::shouldGoToHistoryItem(HistoryItem* item) const
{
    if(item) 
        return true;

    return false;
}

void FrameLoaderClientMC::assignIdentifierToInitialRequest(unsigned long identifier, DocumentLoader*, const ResourceRequest& request)
{
    if (cb_set_status)  {
        String status_msg = statusConnectDefaultLabel() + 
							String::fromUTF8(request.url().url().utf8().data());
		if(m_frame->view())
        	cb_set_status(m_frame->view()->containingView(), status_msg.utf8().data());
    }
}

void FrameLoaderClientMC::frameLoadCompleted()
{
    m_frame->loader()->setPreviousHistoryItem(0);
}

void FrameLoaderClientMC::setMainFrameDocumentReady(bool)
{
    if (cb_set_status) 
        cb_set_status(m_frame->view()->containingView(), statusDoneDefaultLabel().utf8().data());
}

Frame* FrameLoaderClientMC::dispatchCreatePage()
{
    if (cb_open_window){
        FloatRect windowRect = m_frame->page()->chrome()->windowRect();

        WindowFeatures features = {
            windowRect.x(), true,
            windowRect.y(), true,
            windowRect.width(), true,
            windowRect.height(), true,
            true, true, true,
            true, true, true,
            false, false };

        unsigned int styles = 0x3F; // a full feature window not modal.
        _mc_view* view = cb_open_window("about:blank", styles, NULL);
        if (view){
            view->view->mainframe()->page()->chrome()->setWindowFeature(features);
            return view->view->mainframe();
       }  else
            return NULL;
    } else
        return NULL;
}

void FrameLoaderClientMC::dispatchWillFirstLayout()
{
    WebView* view = m_frame->view()->containingView()->view;
	if (view && (m_frame == m_frame->page()->mainFrame())) {
		if (cb_start_layout)
			cb_start_layout(m_frame->view()->containingView());

		view->firstLayout();
	}
}

ObjectContentType FrameLoaderClientMC::objectContentType(const KURL& url, const String& _mimeType)
{
    if (url.isEmpty())
        return ObjectContentNone;

    String mimeType = _mimeType;
    if (! mimeType.length())
        mimeType = MIMETypeRegistry::getMIMETypeForPath(url.url());

    if (! mimeType.length())
        return ObjectContentFrame;

    if (MIMETypeRegistry::isSupportedImageMIMEType(mimeType))
        return ObjectContentImage;

#if ENABLE(PLUGIN)
    if (PlugInInfoStore::supportsMIMEType(mimeType))
        return ObjectContentNetscapePlugin;
#endif

    if (MIMETypeRegistry::isSupportedNonImageMIMEType(mimeType))
        return ObjectContentFrame;

    if (url.protocol() == "about")
        return ObjectContentFrame;

    return ObjectContentNone;
}

bool FrameLoaderClientMC::canHandleRequest(const ResourceRequest& req) const
{
	if (cb_allow_main_request && !cb_allow_main_request(req.url().url().utf8().data()))
		return false;

    if(isSupportedInternalScheme(req.url().protocol().latin1()))
        return true;

    return false;
}

void FrameLoaderClientMC::dispatchDidFailProvisionalLoad(const ResourceError& err)
{
    if (cb_error) 
        cb_error((_mc_error)err.errorCode(), err.failingURL().utf8().data());
}

void FrameLoaderClientMC::dispatchDidFailLoad(const ResourceError& err)
{
    if (cb_error) 
        cb_error((_mc_error)err.errorCode(), err.failingURL().utf8().data());
}

//not implements
void FrameLoaderClientMC::setMainDocumentError(DocumentLoader* l, const ResourceError& err)
{
    notImplemented();
}

void FrameLoaderClientMC::didFinishLoad()
{
    notImplemented();
}

bool FrameLoaderClientMC::privateBrowsingEnabled() const
{
    notImplemented();
    return false;
}

void FrameLoaderClientMC::makeDocumentView()
{
    notImplemented();
}

void FrameLoaderClientMC::makeRepresentation(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::setDocumentViewFromCachedPage(CachedPage*)
{
    notImplemented();
}


void FrameLoaderClientMC::forceLayoutForNonHTML()
{
    notImplemented();
}

void FrameLoaderClientMC::setCopiesOnScroll()
{
    notImplemented();
}

void FrameLoaderClientMC::detachedFromParent2()
{
    notImplemented();
}

void FrameLoaderClientMC::detachedFromParent3()
{
    notImplemented();
}

void FrameLoaderClientMC::detachedFromParent4()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchWillSendRequest(DocumentLoader*, unsigned long identifier, ResourceRequest&, 
                                                                                     const ResourceResponse& redirectResponse)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long identifier, 
                                                                                      const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long identifier, 
                                                                                      const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidReceiveContentLength(DocumentLoader*, unsigned long identifier, int lengthReceived)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidFinishLoading(DocumentLoader*, unsigned long identifier)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidFailLoading(DocumentLoader*, unsigned long identifier, const ResourceError&)
{
    notImplemented();
}

bool FrameLoaderClientMC::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&,
                                                                                  const ResourceResponse&, int length)
{
    notImplemented();
    return false;
}

void FrameLoaderClientMC::dispatchDidHandleOnloadEvents()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidReceiveServerRedirectForProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidCancelClientRedirect()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchWillPerformClientRedirect(const KURL&, double, double)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidChangeLocationWithinPage()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchWillClose()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidReceiveIcon()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidStartProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidCommitLoad()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidFinishDocumentLoad()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidFinishLoad()
{
    notImplemented();
}


void FrameLoaderClientMC::dispatchShow()
{
    notImplemented();
}

void FrameLoaderClientMC::cancelPolicyCheck()
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchUnableToImplementPolicy(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidLoadMainResource(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::revertToProvisionalState(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::clearUnarchivingState(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::startDownload(const ResourceRequest&)
{
    notImplemented();
}

void FrameLoaderClientMC::finishedLoading(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::finalSetupForReplace(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::updateGlobalHistoryForStandardLoad(const KURL&)
{
    notImplemented();
}

void FrameLoaderClientMC::updateGlobalHistoryForReload(const KURL&)
{
    notImplemented();
}

ResourceError FrameLoaderClientMC::cancelledError(const ResourceRequest&)
{
    notImplemented();
    return ResourceError();
}

ResourceError FrameLoaderClientMC::blockedError(const ResourceRequest&)
{
    notImplemented();
    return ResourceError();
}

ResourceError FrameLoaderClientMC::cannotShowURLError(const ResourceRequest&)
{
    notImplemented();
    return ResourceError();
}

ResourceError FrameLoaderClientMC::interruptForPolicyChangeError(const ResourceRequest&)
{
    notImplemented();
    return ResourceError();
}

ResourceError FrameLoaderClientMC::cannotShowMIMETypeError(const ResourceResponse&)
{
    notImplemented();
    return ResourceError();
}

ResourceError FrameLoaderClientMC::fileDoesNotExistError(const ResourceResponse&)
{
    notImplemented();
    return ResourceError();
}

bool FrameLoaderClientMC::shouldFallBack(const ResourceError&)
{
    notImplemented();
    return false;
}

void FrameLoaderClientMC::setDefersLoading(bool)
{
    notImplemented();
}

bool FrameLoaderClientMC::willUseArchive(ResourceLoader*, const ResourceRequest&, const KURL& originalURL) const
{
    notImplemented();
    return false;
}

bool FrameLoaderClientMC::isArchiveLoadPending(ResourceLoader*) const
{
    notImplemented();
    return false;
}

void FrameLoaderClientMC::cancelPendingArchiveLoad(ResourceLoader*)
{
    notImplemented();
}

void FrameLoaderClientMC::clearArchivedResources()
{
    notImplemented();
}

bool FrameLoaderClientMC::representationExistsForURLScheme(const String&) const
{
    notImplemented();
    return false;
}

String FrameLoaderClientMC::generatedMIMETypeForURLScheme(const String&) const
{
    notImplemented();
    return String();
}

void FrameLoaderClientMC::saveViewStateToItem(HistoryItem*)
{
    notImplemented();
}

void FrameLoaderClientMC::restoreViewState()
{
    notImplemented();
}

void FrameLoaderClientMC::provisionalLoadStarted()
{
    notImplemented();
}

void FrameLoaderClientMC::prepareForDataSourceReplacement()
{
    notImplemented();
}

void FrameLoaderClientMC::saveDocumentViewToCachedPage(CachedPage*)
{
    notImplemented();
}

bool FrameLoaderClientMC::canCachePage() const
{
    notImplemented();
    return false;
}

void FrameLoaderClientMC::download(ResourceHandle*, const ResourceRequest&, const ResourceRequest&, const ResourceResponse&)
{
    notImplemented();
}

void FrameLoaderClientMC::redirectDataToPlugin(Widget* pluginWidget)
{
    notImplemented();
}

Widget* FrameLoaderClientMC::createJavaAppletWidget(const IntSize&, Element*, const KURL& baseURL,
                                                     const Vector<String>& paramNames, const Vector<String>& paramValues)
{
    notImplemented();
    return NULL;
}

String FrameLoaderClientMC::overrideMediaType() const
{
    notImplemented();
    return String();
}

void FrameLoaderClientMC::windowObjectCleared() const
{
    notImplemented();
}

void FrameLoaderClientMC::dispatchDidFirstLayout()
{
    notImplemented();
}
}
