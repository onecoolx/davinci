/*
 * PluginViewDavinci.cpp: PluginView implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "PluginView.h"

#include "BridgeJSC.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "HTMLNames.h"
#include "HTMLPlugInElement.h"
#include "HostWindow.h"
#include "JSDOMWindowBase.h"
#include "MouseEvent.h"
#include "NotImplemented.h"
#include "PluginPackage.h"
#include "ScriptController.h"
#include "npruntime_impl.h"
#include "runtime/JSLock.h"
#include "runtime/JSObject.h"
#include "runtime/Operations.h"
#include <wtf/text/CString.h>

namespace WebCore {

using namespace HTMLNames;

#if ENABLE(NETSCAPE_PLUGIN_API)
bool PluginView::dispatchNPEvent(NPEvent& event)
{
    if (!m_plugin->pluginFuncs()->event)
        return false;

    PluginView::setCurrentPluginView(this);
    JSC::JSLock::DropAllLocks dropAllLocks(JSDOMWindowBase::commonVM());
    setCallingPlugin(true);

    bool accepted = m_plugin->pluginFuncs()->event(m_instance, &event);

    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);
    return accepted;
}
#endif

#if defined(XP_UNIX)
void PluginView::handleFocusInEvent()
{
    notImplemented();
}

void PluginView::handleFocusOutEvent()
{
    notImplemented();
}
#endif

void PluginView::handleKeyboardEvent(KeyboardEvent*)
{
    notImplemented();
}

void PluginView::handleMouseEvent(MouseEvent* event)
{
    NPEvent xEvent;

#if defined(XP_UNIX)
    const IntRect rect = parent()->contentsToScreen(IntRect(0, 0, event->offsetX(), event->offsetY()));
    const int eventX = rect.width();
    const int eventY = rect.height();
    if (event->type() == eventNames().mousemoveEvent
            || event->type() == eventNames().mouseoutEvent
            || event->type() == eventNames().mouseoverEvent) {
        xEvent.type = MotionNotify;
        xEvent.xmotion.x = eventX;
        xEvent.xmotion.y = eventY;
    } else if (event->type() == eventNames().mousedownEvent) {
        xEvent.type = ButtonPress;
        xEvent.xbutton.x = eventX;
        xEvent.xbutton.y = eventY;
        xEvent.xbutton.button = event->button() + 1; // DOM MouseEvent counts from 0, and XButtonEvent from 1.
    } else if (event->type() == eventNames().mouseupEvent) {
        xEvent.type = ButtonRelease;
        xEvent.xbutton.x = eventX;
        xEvent.xbutton.y = eventY;
        xEvent.xbutton.button = event->button() + 1;
    } else
        return;
#endif

#if ENABLE(NETSCAPE_PLUGIN_API)
    if (dispatchNPEvent(xEvent))
        event->setDefaultHandled();
#endif
}

void PluginView::updatePluginWidget()
{
    notImplemented();
}

void PluginView::setFocus(bool focused)
{
    if (focused)
        m_element->document()->setFocusedElement(m_element);

    Widget::setFocus(focused);
}

void PluginView::show()
{
    setSelfVisible(true);

    Widget::show();
}

void PluginView::hide()
{
    setSelfVisible(false);

    Widget::hide();
}

void PluginView::paint(GraphicsContext* context, const IntRect& rect)
{
    if (!m_isStarted)
        paintMissingPluginIcon(context, rect);
}

void PluginView::setParent(ScrollView* parent)
{
    Widget::setParent(parent);

    if (parent)
        init();
}

void PluginView::setNPWindowRect(const IntRect&)
{
    notImplemented();
}

void PluginView::setParentVisible(bool visible)
{
    Widget::setParentVisible(visible);
}

#if ENABLE(NETSCAPE_PLUGIN_API)
NPError PluginView::handlePostReadFile(Vector<char>& buffer, uint32_t len, const char* buf)
{
    String filename(buf, len);

    if (filename.startsWith("file:///"))
#if defined(XP_UNIX)
        filename = filename.substring(7);
#else
        filename = filename.substring(8);
#endif

    long long size;
    if (!getFileSize(filename, size))
        return NPERR_FILE_NOT_FOUND;

    FILE* fileHandle = fopen(filename.utf8().data(), "r");
    if (!fileHandle)
        return NPERR_FILE_NOT_FOUND;

    buffer.resize(size);
    int bytesRead = fread(buffer.data(), 1, size, fileHandle);

    fclose(fileHandle);

    if (bytesRead <= 0)
        return NPERR_FILE_NOT_FOUND;

    return NPERR_NO_ERROR;
}
#endif

#if ENABLE(NETSCAPE_PLUGIN_API)
bool PluginView::platformGetValueStatic(NPNVariable variable, void* value, NPError* result)
{
    switch (variable) {
    case NPNVToolkit:
        *static_cast<uint32_t*>(value) = 0;
        *result = NPERR_NO_ERROR;
        return true;

    case NPNVSupportsXEmbedBool:
        *static_cast<NPBool*>(value) = false;
        *result = NPERR_NO_ERROR;
        return true;

    case NPNVjavascriptEnabledBool:
        *static_cast<NPBool*>(value) = true;
        *result = NPERR_NO_ERROR;
        return true;

    case NPNVSupportsWindowless:
        *static_cast<NPBool*>(value) = false;
        *result = NPERR_NO_ERROR;
        return true;

    default:
        return false;
    }
}

bool PluginView::platformGetValue(NPNVariable variable, void* value, NPError* result)
{
    if (!value || !result)
        return false;

    switch (variable) {
    case NPNVxDisplay:
        return true;

    case NPNVxtAppContext:
        *result = NPERR_GENERIC_ERROR;
        return true;

    case NPNVWindowNPObject: {
        if (m_isJavaScriptPaused) {
            *result = NPERR_GENERIC_ERROR;
            return true;
        }

        NPObject* windowScriptObject = m_parentFrame->script().windowScriptNPObject();

        // Return value is expected to be retained, as described here: <http://www.mozilla.org/projects/plugin/npruntime.html>
        if (windowScriptObject)
            _NPN_RetainObject(windowScriptObject);

        *static_cast<void**>(value) = windowScriptObject;

        *result = NPERR_NO_ERROR;
        return true;
    }

    case NPNVPluginElementNPObject: {
        if (m_isJavaScriptPaused) {
            *result = NPERR_GENERIC_ERROR;
            return true;
        }

        NPObject* pluginScriptObject = 0;

        if (m_element->hasTagName(appletTag) || m_element->hasTagName(embedTag) || m_element->hasTagName(objectTag))
            pluginScriptObject = static_cast<HTMLPlugInElement*>(m_element)->getNPObject();

        // Return value is expected to be retained, as described here: <http://www.mozilla.org/projects/plugin/npruntime.html>
        if (pluginScriptObject)
            _NPN_RetainObject(pluginScriptObject);

        *static_cast<void**>(value) = pluginScriptObject;

        *result = NPERR_NO_ERROR;
        return true;
    }

    case NPNVnetscapeWindow: {
        return false;
    }

    case NPNVToolkit:
        if (m_plugin->quirks().contains(PluginQuirkRequiresGtkToolKit)) {
            *static_cast<uint32_t*>(value) = 2;
            *result = NPERR_NO_ERROR;
            return true;
        }
        return false;
    default:
        return false;
    }
}
#endif

void PluginView::invalidateRect(const IntRect& rect)
{
    invalidateWindowlessPluginRect(rect);
}

#if ENABLE(NETSCAPE_PLUGIN_API)
void PluginView::invalidateRect(NPRect* rect)
{
    if (!rect) {
        invalidate();
        return;
    }

    invalidateRect(IntRect(rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top));
}

void PluginView::invalidateRegion(NPRegion)
{
    notImplemented();
}
#endif

void PluginView::forceRedraw()
{
    notImplemented();
}

bool PluginView::platformStart()
{
    ASSERT(m_isStarted);
    ASSERT(m_status == PluginStatusLoadedSuccessfully);

    notImplemented();
    return true;
}

void PluginView::platformDestroy()
{
}

} // namespace WebCore
