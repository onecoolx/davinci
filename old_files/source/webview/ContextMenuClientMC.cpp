/*
** ContextMenuClientMC.cpp: ContextMenuClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"

#include "HitTestResult.h"
#include "KURL.h"
#include "ContextMenu.h"
#include "ContextMenuClientMC.h"
#include "Frame.h"
#include "Page.h"
#include "FrameLoader.h"
#include "ResourceHandle.h"
#include "FrameLoadRequest.h"
#include "ResourceRequest.h"
#include "ResourceHandleInternal.h"
#include "DownloadResourceClient.h"

#include "Debug.h"

namespace WebCore {

ContextMenuClientMC::ContextMenuClientMC()
{
}

ContextMenuClientMC::~ContextMenuClientMC()
{
}
    
void ContextMenuClientMC::downloadURL(const KURL& url)
{
    ResourceRequest request(url, "");
    RefPtr<ResourceHandle> handle = ResourceHandle::create(request, new DownloadResourceClient(true), false, true, true);
    ResourceHandleInternal* d = handle->getInternal();
    d->m_forSavingResource = true;
    d->m_hasDownloadClient = true;
}

void ContextMenuClientMC::searchWithGoogle(const Frame* frame)
{
    String searchString = frame->selectedText();
    searchString.stripWhiteSpace();
    DeprecatedString encoded = KURL::encode_string(searchString.deprecatedString());
    encoded.replace(DeprecatedString("%20"), DeprecatedString("+"));
    
    String url("http://www.google.com/search?q=");
    url.append(String(encoded));
    url.append("&ie=UTF-8&oe=UTF-8");

    ResourceRequest request = ResourceRequest(url);
    if (Page* page = frame->page())
        page->mainFrame()->loader()->urlSelected(FrameLoadRequest(request), 0, false, true);
}

void ContextMenuClientMC::lookUpInDictionary(Frame*)
{
    notImplemented();
}

void ContextMenuClientMC::speak(const String&)
{
    notImplemented();
} 

void ContextMenuClientMC::stopSpeaking()
{
    notImplemented();
}

}
