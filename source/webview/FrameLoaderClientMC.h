/*
** FrameLoaderClient.h: FrameLoaderClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#ifndef WebFrameLoaderClient_H
#define WebFrameLoaderClient_H

#include "FrameLoaderClient.h"
#include "ResourceResponse.h"

namespace WebCore {

class String;
class FrameMC;
struct ResourceRequest;

class FrameLoaderClientMC : public FrameLoaderClient
{
public:
    FrameLoaderClientMC();
    virtual ~FrameLoaderClientMC();

    virtual void frameLoaderDestroyed();

    virtual bool hasWebView() const;
    virtual bool hasFrameView() const;

    virtual bool privateBrowsingEnabled() const;

    virtual void makeDocumentView();
    virtual void makeRepresentation(DocumentLoader*);
    virtual void setDocumentViewFromCachedPage(CachedPage*);
    virtual void forceLayout();
    virtual void forceLayoutForNonHTML();

    virtual void setCopiesOnScroll();

    virtual void detachedFromParent2();
    virtual void detachedFromParent3();
    virtual void detachedFromParent4();

    virtual void assignIdentifierToInitialRequest(unsigned long identifier, DocumentLoader*, const ResourceRequest&);
    virtual void dispatchWillSendRequest(DocumentLoader*, unsigned long identifier, ResourceRequest&, const ResourceResponse& redirectResponse);
    virtual void dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long identifier, const AuthenticationChallenge&);
    virtual void dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long identifier, const AuthenticationChallenge&);        
    virtual void dispatchDidReceiveResponse(DocumentLoader*, unsigned long identifier, const ResourceResponse&);
    virtual void dispatchDidReceiveContentLength(DocumentLoader*, unsigned long identifier, int lengthReceived);
    virtual void dispatchDidFinishLoading(DocumentLoader*, unsigned long identifier);
    virtual void dispatchDidFailLoading(DocumentLoader*, unsigned long identifier, const ResourceError&);
    virtual bool dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&, const ResourceResponse&, int length);

    virtual void dispatchDidHandleOnloadEvents();
    virtual void dispatchDidReceiveServerRedirectForProvisionalLoad();
    virtual void dispatchDidCancelClientRedirect();
    virtual void dispatchWillPerformClientRedirect(const KURL&,
                                                   double, double);
    virtual void dispatchDidChangeLocationWithinPage();
    virtual void dispatchWillClose();
    virtual void dispatchDidReceiveIcon();
    virtual void dispatchDidStartProvisionalLoad();
    virtual void dispatchDidReceiveTitle(const String&);
	virtual void dispatchDidSetLocation(const KURL&);
    virtual void dispatchDidCommitLoad();
    virtual void dispatchDidFailProvisionalLoad(const ResourceError&);
    virtual void dispatchDidFailLoad(const ResourceError&);
    virtual void dispatchDidFinishDocumentLoad();
    virtual void dispatchDidFinishLoad();
    virtual void dispatchDidFirstLayout();
    virtual void dispatchWillFirstLayout();

    virtual Frame* dispatchCreatePage();
    virtual void dispatchShow();

    virtual void dispatchDecidePolicyForMIMEType(FramePolicyFunction, const String& MIMEType, const ResourceRequest&);
    virtual void dispatchDecidePolicyForNewWindowAction(FramePolicyFunction, const NavigationAction&, const ResourceRequest&, const String& frameName);
    virtual void dispatchDecidePolicyForNavigationAction(FramePolicyFunction, const NavigationAction&, const ResourceRequest&);
    virtual void cancelPolicyCheck();

    virtual void dispatchUnableToImplementPolicy(const ResourceError&);

    virtual void dispatchWillSubmitForm(FramePolicyFunction,
                                        PassRefPtr<FormState>);

    virtual void dispatchDidLoadMainResource(DocumentLoader*);
    virtual void revertToProvisionalState(DocumentLoader*);
    virtual void setMainDocumentError(DocumentLoader*, const ResourceError&);
    virtual void clearUnarchivingState(DocumentLoader*);

    virtual void setMainFrameDocumentReady(bool);

    virtual void postProgressStartedNotification();
    virtual void postProgressEstimateChangedNotification();
    virtual void postProgressFinishedNotification();
        
    virtual void startDownload(const ResourceRequest&);

    virtual void willChangeTitle(DocumentLoader*);
    virtual void didChangeTitle(DocumentLoader*);

    virtual void committedLoad(DocumentLoader*, const char*, int);
    virtual void finishedLoading(DocumentLoader*);
    virtual void finalSetupForReplace(DocumentLoader*);

    virtual void updateGlobalHistoryForStandardLoad(const KURL&);
    virtual void updateGlobalHistoryForReload(const KURL&);
    virtual bool shouldGoToHistoryItem(HistoryItem*) const;

    virtual ResourceError cancelledError(const ResourceRequest&);
    virtual ResourceError blockedError(const ResourceRequest&);
    virtual ResourceError cannotShowURLError(const ResourceRequest&);
    virtual ResourceError interruptForPolicyChangeError(const ResourceRequest&);

    virtual ResourceError cannotShowMIMETypeError(const ResourceResponse&);
    virtual ResourceError fileDoesNotExistError(const ResourceResponse&);

    virtual bool shouldFallBack(const ResourceError&);

    virtual void setDefersLoading(bool);

    virtual bool willUseArchive(ResourceLoader*, const ResourceRequest&, const KURL& originalURL) const;
    virtual bool isArchiveLoadPending(ResourceLoader*) const;
    virtual void cancelPendingArchiveLoad(ResourceLoader*);
    virtual void clearArchivedResources();

    virtual bool canHandleRequest(const ResourceRequest&) const;
    virtual bool canShowMIMEType(const String&) const;
    virtual bool representationExistsForURLScheme(const String&) const;
    virtual String generatedMIMETypeForURLScheme(const String&) const;

    virtual void frameLoadCompleted();
    virtual void saveViewStateToItem(HistoryItem*);
    virtual void restoreViewState();
    virtual void provisionalLoadStarted();
    virtual void didFinishLoad();
    virtual void prepareForDataSourceReplacement();

    virtual PassRefPtr<DocumentLoader> createDocumentLoader(const ResourceRequest&, const SubstituteData&);
    virtual void setTitle(const String& title, const KURL&);

    virtual String userAgent(const KURL&);

    virtual void saveDocumentViewToCachedPage(CachedPage*);
    virtual bool canCachePage() const;
    virtual void download(ResourceHandle*, const ResourceRequest&, const ResourceRequest&, const ResourceResponse&);

    virtual PassRefPtr<Frame> createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement,
            const String& referrer, ScrollbarMode modeScrolling, int marginWidth, int marginHeight);
    virtual Widget* createPlugin(const IntSize&, Element*, const KURL&, const Vector<String>&, const Vector<String>&, const String&, bool loadManually);
    virtual void redirectDataToPlugin(Widget* pluginWidget);
    virtual Widget* createJavaAppletWidget(const IntSize&, Element*, const KURL& baseURL, const Vector<String>& paramNames, const Vector<String>& paramValues);

    virtual ObjectContentType objectContentType(const KURL& url, const String& mimeType);
    virtual String overrideMediaType() const;

    virtual void windowObjectCleared() const;
        
    virtual void didPerformFirstNavigation() const{}
        
    virtual void registerForIconNotification(bool listen = true){}
public:
    void setFrame (Frame * frame){m_frame = frame;}
private:
    Frame *m_frame;
    ResourceResponse m_response;
    bool m_firstData;
};

}

#endif // FrameLoaderClientWin_H
