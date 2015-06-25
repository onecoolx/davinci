/*
** Widget.cpp: Widget implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "Widget.h"

#include "Cursor.h"
#include "Document.h"
#include "Element.h"
#include "GraphicsContext.h"
#include "IntRect.h"
#include "FrameView.h"
#include "WidgetClient.h"
#include "Debug.h"

#include "macross.h"
#include "WebView.h"
#include "WebEngine.h"
#include "WebCallback.h"

namespace WebCore {

class WidgetPrivate
{
public:
    WidgetClient* client;
    ScrollView* parent;
    _mc_view* containingView;
    IntRect frameRect;
    bool enabled;
    Widget* capturingChild;
    bool suppressInvalidation;
};

Widget::Widget()
    : data(new WidgetPrivate)
{
    data->client = 0;
    data->parent = 0;
    data->containingView = 0;
    data->enabled = true;
    data->capturingChild = 0;
    data->suppressInvalidation = false;
}

Widget::~Widget() 
{
    delete data;
}

void Widget::setContainingView(_mc_view* view)
{
    data->containingView = view;
}

_mc_view* Widget::containingView() const
{
    return data->containingView;
}

void Widget::setClient(WidgetClient* c)
{
    data->client = c;
}

WidgetClient* Widget::client() const
{
    return data->client;
}

IntRect Widget::frameGeometry() const
{
    return data->frameRect;
}

void Widget::setFrameGeometry(const IntRect &rect)
{
    data->frameRect = rect;
}

void Widget::setParent(ScrollView* v)
{
    data->parent = v;
}

ScrollView* Widget::parent() const
{
    return data->parent;
}

void Widget::removeFromParent()
{
    if (parent())
        parent()->removeChild(this);
}

MC_CURSOR lastSetCursor = POINTER_CURSOR;
bool ignoreNextSetCursor = false;

void Widget::setCursor(const Cursor& cursor)
{
    // This is set by PluginViewWin so it can ignore set setCursor call made by
    // EventHandler.cpp.
    if (ignoreNextSetCursor) {
        ignoreNextSetCursor = false;
        return;
    }

    MC_CURSOR c = cursor.impl();
    lastSetCursor = c;
	if (cb_set_cursor)
		cb_set_cursor(c);
}

IntPoint Widget::convertToContainingWindow(const IntPoint& point) const
{
    IntPoint windowPoint = point;
    for (const Widget *parentWidget = parent(), *childWidget = this;
         parentWidget;
         childWidget = parentWidget, parentWidget = parentWidget->parent())
        windowPoint = parentWidget->convertChildToSelf(childWidget, windowPoint);
    return windowPoint;
}

IntPoint Widget::convertFromContainingWindow(const IntPoint& point) const
{
    IntPoint widgetPoint = point;
    for (const Widget *parentWidget = parent(), *childWidget = this;
         parentWidget;
         childWidget = parentWidget, parentWidget = parentWidget->parent())
        widgetPoint = parentWidget->convertSelfToChild(childWidget, widgetPoint);
    return widgetPoint;
}

IntRect Widget::convertToContainingWindow(const IntRect& rect) const
{
    IntRect convertedRect = rect;
    convertedRect.setLocation(convertToContainingWindow(convertedRect.location()));
    return convertedRect;
}

IntPoint Widget::convertChildToSelf(const Widget* child, const IntPoint& point) const
{
    return IntPoint(point.x() + child->x(), point.y() + child->y());
}

IntPoint Widget::convertSelfToChild(const Widget* child, const IntPoint& point) const
{
    return IntPoint(point.x() - child->x(), point.y() - child->y());
}


bool Widget::isEnabled() const
{
    return data->enabled;
}

void Widget::setEnabled(bool e)
{
    if (e != data->enabled) {
        data->enabled = e;
        invalidate();
    }
}

bool Widget::suppressInvalidation() const
{
    return data->suppressInvalidation;
}

void Widget::setSuppressInvalidation(bool suppress)
{
    data->suppressInvalidation = suppress;
}

void Widget::invalidate()
{
    invalidateRect(IntRect(0, 0, width(), height()));
}

void Widget::invalidateRect(const IntRect& r)
{
    if (data->suppressInvalidation)
        return;

    if (!parent()) {
		if (data->containingView && data->containingView->view)
	  		data->containingView->view->updateRect(r.x(), r.y(), r.width(), r.height());
        if (isFrameView())
            static_cast<FrameView*>(this)->addToDirtyRegion(r);
        return;
    }

    // Get the root widget.
    ScrollView* outermostView = parent();
    while (outermostView && outermostView->parent())
        outermostView = outermostView->parent();
    if (!outermostView)
        return;

    IntRect windowRect = convertToContainingWindow(r);

    // Get our clip rect and intersect with it to ensure we don't invalidate too much.
    IntRect clipRect = windowClipRect();
    windowRect.intersect(clipRect);

	if (data->containingView && data->containingView->view)
		data->containingView->view->updateRect(windowRect.x(), windowRect.y(), 
												windowRect.width(), windowRect.height());
    outermostView->addToDirtyRegion(windowRect);
}

void Widget::show()
{
}

void Widget::hide()
{
}

void Widget::setFocus()
{
}

void Widget::paint(GraphicsContext*, const IntRect&)
{
}

void Widget::setIsSelected(bool) 
{
    notImplemented();
}

} // namespace WebCore
