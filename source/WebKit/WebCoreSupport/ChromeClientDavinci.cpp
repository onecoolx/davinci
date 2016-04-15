/*
 * ChromeClientDavinci.cpp: ChromeClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "ChromeClientDavinci.h"

#include "FileChooser.h"
#include "FileIconLoader.h"
#include "Icon.h"
#include "NotImplemented.h"
#include "NavigationAction.h"
#if 0
#include "PopupMenuWin.h"
#include "SearchPopupMenuWin.h"
#endif
#include "WebView.h"
#include <wtf/text/CString.h>

using namespace WebCore;

namespace WebKit {

ChromeClientDavinci::ChromeClientDavinci(WebView* webView)
    : m_webView(webView)
{
    ASSERT(m_webView);
}

void ChromeClientDavinci::chromeDestroyed()
{
    delete this;
}

FloatRect ChromeClientDavinci::windowRect()
{
    if (!m_webView)
        return FloatRect();

#if 0
    m_webView->frameRect(&rect);
    return rect;
#else
	return FloatRect();
#endif
}

void ChromeClientDavinci::setWindowRect(const FloatRect&)
{
    notImplemented();
}

FloatRect ChromeClientDavinci::pageRect()
{
    return windowRect();
}

void ChromeClientDavinci::focus()
{
    notImplemented();
}

void ChromeClientDavinci::unfocus()
{
    notImplemented();
}

Page* ChromeClientDavinci::createWindow(Frame*, const FrameLoadRequest&, const WindowFeatures&, const NavigationAction&)
{
    notImplemented();
    return 0;
}

void ChromeClientDavinci::show()
{
    notImplemented();
}

bool ChromeClientDavinci::canRunModal()
{
    notImplemented();
    return false;
}

void ChromeClientDavinci::runModal()
{
    notImplemented();
}

void ChromeClientDavinci::setToolbarsVisible(bool)
{
    notImplemented();
}

bool ChromeClientDavinci::toolbarsVisible()
{
    return false;
}

void ChromeClientDavinci::setStatusbarVisible(bool)
{
    notImplemented();
}

bool ChromeClientDavinci::statusbarVisible()
{
    notImplemented();
    return false;
}

void ChromeClientDavinci::setScrollbarsVisible(bool)
{
    notImplemented();
}

bool ChromeClientDavinci::scrollbarsVisible()
{
    notImplemented();
    return false;
}

void ChromeClientDavinci::setMenubarVisible(bool)
{
    notImplemented();
}

bool ChromeClientDavinci::menubarVisible()
{
    notImplemented();
    return false;
}

void ChromeClientDavinci::setResizable(bool)
{
    notImplemented();
}

void ChromeClientDavinci::closeWindowSoon()
{

}

bool ChromeClientDavinci::canTakeFocus(FocusDirection)
{
    return true;
}

void ChromeClientDavinci::takeFocus(FocusDirection)
{
    unfocus();
}

void ChromeClientDavinci::focusedElementChanged(Element*)
{
    notImplemented();
}

void ChromeClientDavinci::focusedFrameChanged(Frame*)
{
}

bool ChromeClientDavinci::canRunBeforeUnloadConfirmPanel()
{
    return true;
}

bool ChromeClientDavinci::runBeforeUnloadConfirmPanel(const String& message, Frame* frame)
{
    return runJavaScriptConfirm(frame, message);
}

void ChromeClientDavinci::addMessageToConsole(MessageSource, MessageLevel, const String&, unsigned, unsigned, const String&)
{
    notImplemented();
}

void ChromeClientDavinci::runJavaScriptAlert(Frame*, const String& message)
{
#if 0
    m_webView->runJavaScriptAlert(message);
#endif
}

bool ChromeClientDavinci::runJavaScriptConfirm(Frame*, const String& message)
{
#if 0
    return m_webView->runJavaScriptConfirm(message);
#else
	return false;
#endif
}

bool ChromeClientDavinci::runJavaScriptPrompt(Frame*, const String& message, const String& defaultValue, String& result)
{
#if 0
    return m_webView->runJavaScriptPrompt(message, defaultValue, result);
#else
	return false;
#endif
}

void ChromeClientDavinci::setStatusbarText(const String&)
{
    notImplemented();
}

bool ChromeClientDavinci::shouldInterruptJavaScript()
{
    notImplemented();
    return false;
}

KeyboardUIMode ChromeClientDavinci::keyboardUIMode()
{
    return KeyboardAccessTabsToLinks;
}

IntRect ChromeClientDavinci::windowResizerRect() const
{
    notImplemented();
    return IntRect();
}

void ChromeClientDavinci::invalidateRootView(const IntRect&, bool)
{
    notImplemented();
}

void ChromeClientDavinci::invalidateContentsAndRootView(const IntRect& updateRect, bool immediate)
{
#if 0
    RECT rect = updateRect;
    InvalidateRect(m_webView->windowHandle(), &rect, FALSE);

    if (immediate)
        UpdateWindow(m_webView->windowHandle());
#endif
}

void ChromeClientDavinci::invalidateContentsForSlowScroll(const IntRect& updateRect, bool immediate)
{
    invalidateContentsAndRootView(updateRect, immediate);
}

void ChromeClientDavinci::scroll(const IntSize&, const IntRect& rectToScroll, const IntRect&)
{
    invalidateContentsAndRootView(rectToScroll, false);
}

IntRect ChromeClientDavinci::rootViewToScreen(const IntRect& rect) const
{
    notImplemented();
    return rect;
}

IntPoint ChromeClientDavinci::screenToRootView(const IntPoint& point) const
{
    notImplemented();
    return point;
}

PlatformPageClient ChromeClientDavinci::platformPageClient() const
{
    notImplemented();
    return 0;
}

void ChromeClientDavinci::contentsSizeChanged(Frame*, const IntSize&) const
{
    notImplemented();
}

void ChromeClientDavinci::scrollRectIntoView(const IntRect&) const
{
    notImplemented();
}

void ChromeClientDavinci::scrollbarsModeDidChange() const
{
    notImplemented();
}

void ChromeClientDavinci::mouseDidMoveOverElement(const HitTestResult&, unsigned)
{
    notImplemented();
}

void ChromeClientDavinci::setToolTip(const String&, TextDirection)
{
    notImplemented();
}

void ChromeClientDavinci::print(Frame*)
{
    notImplemented();
}

#if ENABLE(SQL_DATABASE)
void ChromeClientDavinci::exceededDatabaseQuota(Frame*, const String&, DatabaseDetails)
{
    notImplemented();
}
#endif

void ChromeClientDavinci::reachedMaxAppCacheSize(int64_t)
{
    notImplemented();
}

void ChromeClientDavinci::reachedApplicationCacheOriginQuota(SecurityOrigin*, int64_t)
{
    notImplemented();
}

#if ENABLE(TOUCH_EVENTS)
void ChromeClientDavinci::needTouchEvents(bool)
{
    notImplemented();
}
#endif

#if USE(ACCELERATED_COMPOSITING)
void ChromeClientDavinci::attachRootGraphicsLayer(Frame*, GraphicsLayer*)
{
    notImplemented();
}

void ChromeClientDavinci::setNeedsOneShotDrawingSynchronization()
{
    notImplemented();
}

void ChromeClientDavinci::scheduleCompositingLayerFlush()
{
    notImplemented();
}
#endif

void ChromeClientDavinci::runOpenPanel(Frame*, PassRefPtr<FileChooser> prpFileChooser)
{
    notImplemented();
}

void ChromeClientDavinci::loadIconForFiles(const Vector<String>& filenames, FileIconLoader* loader)
{
    loader->notifyFinished(Icon::createIconForFiles(filenames));
}

void ChromeClientDavinci::setCursor(const Cursor&)
{
    notImplemented();
}

void ChromeClientDavinci::setCursorHiddenUntilMouseMoves(bool)
{
    notImplemented();
}

void ChromeClientDavinci::setLastSetCursorToCurrentCursor()
{
    notImplemented();
}

void ChromeClientDavinci::AXStartFrameLoad()
{
    notImplemented();
}

void ChromeClientDavinci::AXFinishFrameLoad()
{
    notImplemented();
}

void ChromeClientDavinci::formStateDidChange(const Node*)
{
    notImplemented();
}

bool ChromeClientDavinci::selectItemWritingDirectionIsNatural()
{
    return false;
}

bool ChromeClientDavinci::selectItemAlignmentFollowsMenuWritingDirection()
{
    return false;
}

bool ChromeClientDavinci::hasOpenedPopup() const
{
    notImplemented();
    return false;
}

PassRefPtr<PopupMenu> ChromeClientDavinci::createPopupMenu(PopupMenuClient* client) const
{
#if 0
    return adoptRef(new PopupMenuWin(client));
#else
	return 0;
#endif
}

PassRefPtr<SearchPopupMenu> ChromeClientDavinci::createSearchPopupMenu(PopupMenuClient* client) const
{
#if 0
    return adoptRef(new SearchPopupMenuWin(client));
#else
	return 0;
#endif
}

} // namespace WebKit
