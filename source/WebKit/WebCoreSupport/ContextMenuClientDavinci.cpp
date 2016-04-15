/*
 * ContextMenuClientDavinci.cpp: ContextMenuClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "ContextMenuClientDavinci.h"

#include "ContextMenu.h"
#include "NotImplemented.h"

using namespace WebCore;

namespace WebKit {

ContextMenuClientDavinci::ContextMenuClientDavinci(WebView *webView)
    : m_webView(webView)
{
}

void ContextMenuClientDavinci::contextMenuDestroyed()
{
    delete this;
}

PassOwnPtr<ContextMenu> ContextMenuClientDavinci::customizeMenu(PassOwnPtr<ContextMenu> menu)
{
    return menu;
}

void ContextMenuClientDavinci::contextMenuItemSelected(ContextMenuItem*, const ContextMenu*)
{
    notImplemented();
}

void ContextMenuClientDavinci::downloadURL(const KURL& url)
{
    notImplemented();
}

void ContextMenuClientDavinci::copyImageToClipboard(const HitTestResult&)
{
    notImplemented();
}

void ContextMenuClientDavinci::searchWithGoogle(const Frame*)
{
    notImplemented();
}

void ContextMenuClientDavinci::lookUpInDictionary(Frame*)
{
    notImplemented();
}

void ContextMenuClientDavinci::speak(const String&)
{
    notImplemented();
}

void ContextMenuClientDavinci::stopSpeaking()
{
    notImplemented();
}

bool ContextMenuClientDavinci::isSpeaking()
{
    notImplemented();
    return false;
}

} // namespace WebKit
