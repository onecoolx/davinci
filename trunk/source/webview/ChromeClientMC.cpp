/*
** ChromeClient.cpp: ChromeClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"

#include "macross.h"
#include "ChromeClientMC.h"

#include "Frame.h"
#include "Page.h"
#include "FrameView.h"
#include "FrameLoader.h"
#include "CString.h"
#include "FrameLoadRequest.h"
#include "HitTestResult.h"
#include "Debug.h"

#include "WebView.h"
#include "WebEngine.h"
#include "WebCallback.h"

using namespace MaCross;

namespace WebCore
{
    
ChromeClientMC::ChromeClientMC(_mc_view* view, int width, int height)
    :m_view(view)
    ,m_lastHoverElement(0)
    ,m_lastTooltipId(0)
    ,m_focused(false)
{
    // default window features.
    // FIXME: the width and height is control's not window's
    m_features.x = 0.0f;
    m_features.xSet = false;
    m_features.y = 0.0f;
    m_features.ySet = false;
    m_features.width = width;
    m_features.widthSet = false;
    m_features.height = height;
    m_features.heightSet = false;
    m_features.menuBarVisible = true;
    m_features.statusBarVisible = true;
    m_features.toolBarVisible = true;
    m_features.locationBarVisible = true;
    m_features.scrollbarsVisible = true;
    m_features.resizable = true;
    m_features.fullscreen = false;
    m_features.dialog = false;
}

ChromeClientMC::~ChromeClientMC()
{
    
}

void ChromeClientMC::addToDirtyRegion(const IntRect& rect)
{
}

void ChromeClientMC::scrollBackingStore(int dx, int dy, const IntRect& scrollViewRect, const IntRect& clipRect)
{
}

void ChromeClientMC::updateBackingStore()
{
}

void ChromeClientMC::runJavaScriptAlert(Frame* frame, const String& message)
{
    String text = message;
    text.replace('\\', frame->backslashAsCurrencySymbol());
    UChar nullChar = 0;
    text += String(&nullChar, 1);

    if (cb_alert_box)
        cb_alert_box(frame->view()->containingView(), (char*)text.utf8().data());
}

bool ChromeClientMC::runJavaScriptConfirm(Frame* frame, const String& message)
{
    int ret = 0;
    String text = message;
    text.replace('\\', frame->backslashAsCurrencySymbol());
    UChar nullChar = 0;
    text += String(&nullChar, 1);

    if (cb_confirm_box)
        ret = cb_confirm_box(frame->view()->containingView(), (char*)text.utf8().data());

    return (ret ? true : false);
}

bool ChromeClientMC::runJavaScriptPrompt(Frame* frame, const String& message, const String& defaultValue, String& result)
{
    char * ret = NULL;

    String text = message;
    String def_text = defaultValue;
    text.replace('\\', frame->backslashAsCurrencySymbol());
    def_text.replace('\\', frame->backslashAsCurrencySymbol());
    UChar nullChar = 0;
    text += String(&nullChar, 1);
    def_text += String(&nullChar, 1);

    if (cb_prompt_box)
       ret = cb_prompt_box(frame->view()->containingView(), (char*)text.utf8().data(), (char*)def_text.utf8().data());

    if (ret){
        result = String::fromUTF8(ret);
        return true;
    } else
        return false; 
}

bool ChromeClientMC::tabsToLinks() const
{
    return true;
}

void ChromeClientMC::setWindowFeature(const WindowFeatures& features)
{
    m_features = features;
}

Page* ChromeClientMC::createWindow(Frame* frame, const FrameLoadRequest& request, const WindowFeatures& features)
{
    if (cb_open_window){
        int x, y, width, height;
        unsigned styles = 0;

        if (features.xSet) 
            x = (int)ceil(features.x); 
        else
            x = 0;

        if (features.ySet)
            y = (int)ceil(features.y);
        else
            y = 0;

        if (features.widthSet)
            width = (int)ceil(features.width);
        else
            width = -1; //normal size

        if (features.heightSet)
            height = (int)ceil(features.height);
        else
            height = -1; //normal size

        if (features.toolBarVisible)
            styles |= MC_TOOLBAR;

        if (features.locationBarVisible)
            styles |= MC_LOCATIONBAR;

        if (features.statusBarVisible)
            styles |= MC_STATUSBAR;

        if (features.scrollbarsVisible)
            styles |= MC_SCROLLBARS;

        if (features.menuBarVisible)
            styles |= MC_MENUBAR;

        if (features.resizable)
            styles |= MC_RESIZABLE;
        
        if (features.dialog)
            styles |= MC_MODAL;

		_mc_rect rc = {x, y, width, height};
		bool normal = false;	
		if ((width == -1) || (height == -1))
			normal = true;

        _mc_view* view = cb_open_window(request.resourceRequest().url().url().utf8().data(),
                                                					styles, (normal ? 0 : &rc));
        if (view) {
            Page * page = view->view->mainframe()->page();
            page->chrome()->setWindowFeature(features);
            return page;
        }else
            return NULL;
    } else
        return NULL;
}

bool ChromeClientMC::canRunModal()
{
    return true;
}

void ChromeClientMC::closeWindowSoon()
{
    if (cb_close_window)
        cb_close_window(m_view);
}

void ChromeClientMC::setStatusbarText(const String& text)
{
    if (cb_set_status)
        cb_set_status(m_view, text.utf8().data());
}

bool ChromeClientMC::locationbarVisible()
{
    return m_features.locationBarVisible;
}

bool ChromeClientMC::personalbarVisible()
{
    return m_features.toolBarVisible;
}

bool ChromeClientMC::toolbarVisible()
{
    return m_features.toolBarVisible;
}

bool ChromeClientMC::statusbarVisible()
{
    return m_features.statusBarVisible;
}

bool ChromeClientMC::scrollbarsVisible()
{
    return m_features.scrollbarsVisible;
}

bool ChromeClientMC::menubarVisible()
{
    return m_features.menuBarVisible;
}

FloatRect ChromeClientMC::windowRect()
{
    return FloatRect(m_features.x, m_features.y, m_features.width, m_features.height);
}

void ChromeClientMC::mouseDidMoveOverElement(const HitTestResult& result, unsigned modifierFlags)
{
    Element *link = result.URLElement();
    if (link != m_lastHoverElement) {
        m_lastHoverElement = link;
        if (cb_set_status)
            cb_set_status(m_view, result.absoluteLinkURL().prettyURL().utf8().data());
    }
}

void ChromeClientMC::setToolTip(const String& str, const IntPoint & mouse_point)
{
    unsigned int ns = 0;
    bool bShow = !str.isEmpty();
    
    bool canSetTip = (bShow && ((ns = str.impl()->hash()) != m_lastTooltipId));
    if (canSetTip && cb_show_tooltip) {
        cb_show_tooltip(m_view, mouse_point.x(), mouse_point.y(), str.utf8().data()); 
        m_lastTooltipId = ns;
    }
}

void ChromeClientMC::focus()
{
    if (!m_focused) {
        m_focused = true;
		if (cb_set_focus)
			cb_set_focus(m_view);
    }
}


void ChromeClientMC::unfocus()
{
    if (m_focused) {
        m_focused = false;
		if (cb_kill_focus)
			cb_kill_focus(m_view);
    }
}

void ChromeClientMC::focusChangedRect(const IntRect& r)
{
	if (cb_change_focus) {
		_mc_rect rc = {r.x(), r.y(), r.width(), r.height()};
		cb_change_focus(m_view, &rc);
	}
}

//not implement.
float ChromeClientMC::scaleFactor()
{
    notImplemented();
    return 1.0f;
}

bool ChromeClientMC::canTakeFocus(FocusDirection)
{
    notImplemented();
    return false;
}

void ChromeClientMC::takeFocus(FocusDirection)
{
    notImplemented();
}


void ChromeClientMC::runModal()
{
    notImplemented();
}

void ChromeClientMC::setWindowRect(const FloatRect&)
{
    notImplemented();
}

void ChromeClientMC::addMessageToConsole(const String& message, unsigned int lineNumber, const String& sourceID)
{
    notImplemented();
}

bool ChromeClientMC::canRunBeforeUnloadConfirmPanel()
{
    notImplemented();
    return false;
}

bool ChromeClientMC::runBeforeUnloadConfirmPanel(const String& message, Frame* frame)
{
    notImplemented();
    return false;
}

bool ChromeClientMC::shouldInterruptJavaScript()
{
    notImplemented();
    return false;
}


IntRect ChromeClientMC::windowResizerRect() const
{
    notImplemented();
    return IntRect();
}

void ChromeClientMC::print(Frame*)
{
    notImplemented();
}


}
