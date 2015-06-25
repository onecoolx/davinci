/*
** webview.cpp: webview implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include <picasso.h>

#include <wtf/StringExtras.h>

#include "Page.h"
#include "Frame.h"
#include "FrameTree.h"
#include "FrameView.h"
#include "FrameLoader.h"
#include "DocumentLoader.h"
#include "Editor.h"
#include "EventHandler.h"
#include "GraphicsContext.h"
#include "Settings.h"
#include "ContextMenu.h"
#include "SchemeExtension.h"
#include "SubstituteData.h"

#include "ChromeClientMC.h"
#include "ContextMenuClientMC.h"
#include "EditorClientMC.h"
#include "DragClientMC.h"
#include "InspectorClientMC.h"
#include "FrameLoaderClientMC.h"
#include "FocusController.h"
#include "GCController.h"

#include "WebView.h"
#include "WebEngine.h"
#include "WebEncoding.h"
#include "WebCallback.h"

using namespace WTF;
using namespace WebCore;

namespace WebCore {
extern ps_color_format pixelFormat(void);
extern ps_context* getGlobalContext(void);
}

namespace MaCross {

static void garbageRelease(void)
{
	WebCore::gcController().garbageCollectSoon();
}

class WebViewPrivate
{
public:
	WebViewPrivate(struct _mc_view* v, unsigned char* buf, int w, int h, int p)
		: m_view(v), m_buffer(buf), m_width(w), m_height(h), m_mode(0), m_txtanti(false)
		, m_canvas(0), m_context(0), m_drawRect(0, 0, 0, 0), m_minLayoutSize(0, 0), m_oldLayoutSize(0, 0)
	{
		m_canvas = ps_canvas_create_with_data(buf, pixelFormat(), w, h, p);
		m_context = ps_context_create(m_canvas);
		ps_set_filter(m_context, FILTER_NEAREST);
	}

	~WebViewPrivate()
	{
		ps_context_unref(m_context);
		ps_canvas_unref(m_canvas);
	}

	void resizeView(unsigned char* buf, int w, int h, int p)
	{
		ps_context_unref(m_context);
		ps_canvas_unref(m_canvas);
		
		m_buffer = buf;
		m_width = w;
		m_height = h;

		m_canvas = ps_canvas_create_with_data(buf, pixelFormat(), w, h, p);
		m_context = ps_context_create(m_canvas);
		ps_set_filter(m_context, FILTER_NEAREST);
	}

	struct _mc_view* m_view;
	unsigned char* m_buffer;
	int m_width;
	int m_height;
	int m_mode;
	bool m_txtanti;
	ps_canvas* m_canvas;
	ps_context* m_context;
	// webkit object
	IntRect m_drawRect;
	IntSize m_minLayoutSize;
	IntSize m_oldLayoutSize;
    RefPtr<Frame> m_frame;
    RefPtr<FrameView> m_frameView;
};

static Frame *incrementFrame(Frame *curr, bool forward, bool wrapFlag)
{
    return forward ? curr->tree()->traverseNextWithWrap(wrapFlag)
                   : curr->tree()->traversePreviousWithWrap(wrapFlag);
}


// webview 
WebView::WebView(struct _mc_view* view, unsigned char* buffer, int width, int height, int pitch)
	:d(new WebViewPrivate(view, buffer, width, height, pitch))
{
    Settings::init(); 
	ps_set_text_antialias(d->m_context, isTextAntialias() ? True : False);
	d->m_txtanti = isTextAntialias();
	//FIXME: Chrome 's width and height is not view , is window
    Page* page = new Page(new ChromeClientMC(view, width, height), new ContextMenuClientMC,
                          new EditorClientMC(view), new DragClientMC, new InspectorClientMC);
    FrameLoaderClientMC *client = new FrameLoaderClientMC;
    Frame* frame = new Frame(page, 0, client);
	client->setFrame(frame);
	d->m_frame = frame;

	FrameView* frameView = new FrameView(frame);
	frameView->resize(width, height);//set view size
	d->m_frameView = frameView;
    d->m_frame->setView(frameView);
    d->m_frameView->setContainingView(view);
    frameView->deref();

    d->m_frame->init();
    d->m_frame->page()->setGroupName(String("PageGroup"));
}

WebView::~WebView()
{
    stop();
    Page* page = d->m_frame->page();
    Frame *frame = page->mainFrame();
    if (frame)
        frame->loader()->detachFromParent();
    delete page;
	garbageRelease();
}

Frame * WebView::mainframe(void)
{
    return d->m_frame.get();
}

void WebView::resizeView(unsigned char* buffer, int width, int height, int pitch)
{
	if ((d->m_buffer != buffer) || (d->m_width != width) || (d->m_height != height)) {
		d->resizeView(buffer, width, height, pitch);
		ps_set_text_antialias(d->m_context, isTextAntialias() ? True : False);
		d->m_txtanti = isTextAntialias();
	}
    d->m_frameView->resize(width, height);
    d->m_frame->sendResizeEvent();
}

void WebView::scrollRect(int sx, int sy, int x, int y, int width, int height)
{
	updateRect(x, y, width, height);
}

void WebView::updateRect(int x, int y, int width, int height)
{
	d->m_drawRect.unite(IntRect(x, y, width, height));

	if (cb_invalidate_rect) {
		IntRect rc = d->m_drawRect;
		_mc_rect r = {rc.x(), rc.y(), rc.width(), rc.height()};
		cb_invalidate_rect(d->m_view, &r);
	}
}

void WebView::setDirtyRect(int x, int y, int width, int height)
{
	d->m_drawRect.unite(IntRect(x, y, width, height));
}

_mc_size WebView::getSize(void) const
{
	_mc_size size = {d->m_width, d->m_height};
	return size;
}

void WebView::setMinLayoutSize(int w, int h)
{
	d->m_minLayoutSize = IntSize(w, h);
	d->m_frameView->setNeedsLayout();
	d->m_frameView->resize(w, h);
	reflow();
}

void WebView::clearMinLayoutSize(void)
{
	if (!d->m_minLayoutSize.isEmpty()) {
		d->m_minLayoutSize = IntSize(0, 0);
		d->m_oldLayoutSize = IntSize(0, 0);
		d->m_frameView->setNeedsLayout();
		d->m_frameView->resize(d->m_width, d->m_height);
		reflow();
	}
}

void WebView::contentsPosChanged(int old_x, int old_y, int new_x, int new_y)
{
	if (cb_position_changed)
		cb_position_changed(d->m_view, old_x, old_y, new_x, new_y);
}

void WebView::updateViewNow(void)
{
	if (cb_update_view_now)
		cb_update_view_now(d->m_view);
}

void WebView::paintView(void)
{
	Settings* setting = Settings::globalSettings();
	if (d->m_txtanti != setting->textAntialias()) {
		ps_set_text_antialias(d->m_context, isTextAntialias() ? True : False);
		d->m_txtanti = isTextAntialias();
	}

	d->m_frameView->layoutIfNeededRecursive();
	//last draw update rect
	if (!d->m_drawRect.isEmpty()) {
		GraphicsContext gc(d->m_context);
		gc.save();
		gc.clip(d->m_drawRect);
		d->m_frameView->paint(&gc, d->m_drawRect);
		gc.restore();
		d->m_drawRect = IntRect(0, 0, 0, 0); //clear the invalidate Rect 
	}
}

bool WebView::mouseUp(_mc_mouse_btn btn, unsigned m, int x, int y)
{
	IntPoint p(x, y);
	PlatformMouseEvent mouseEvent(MouseEventReleased, _get_mouse_button(btn), p, m);
    return d->m_frame->eventHandler()->handleMouseReleaseEvent(mouseEvent);
}

bool WebView::mouseDown(_mc_mouse_btn btn, unsigned m, int x, int y)
{
	IntPoint p(x, y);
	PlatformMouseEvent mouseEvent(MouseEventPressed, _get_mouse_button(btn), p, m);
    return d->m_frame->eventHandler()->handleMousePressEvent(mouseEvent);
}

bool WebView::mouseMove(_mc_mouse_btn btn, unsigned m, int x, int y)
{
	IntPoint p(x, y);
	PlatformMouseEvent mouseEvent(MouseEventMoved, _get_mouse_button(btn), p, m);
    return d->m_frame->eventHandler()->handleMouseMoveEvent(mouseEvent);
}

bool WebView::mouseWheel(_mc_mouse_btn btn, unsigned m, int x, int y)
{
	int delta = 0;
	if(btn == MOUSE_WHEEL_UP)
		delta = -10;
	else
		delta = 10;
	IntPoint p(x, y);
	PlatformWheelEvent wheelEvent(delta, p, m);
    return d->m_frame->eventHandler()->handleWheelEvent(wheelEvent);
}

bool WebView::keyUp(_mc_key_sym key, unsigned m)
{
	PlatformKeyboardEvent keyEvent(false, (unsigned)key, m);
	Frame* frame = d->m_frame->page()->focusController()->focusedOrMainFrame();
	return frame->eventHandler()->keyEvent(keyEvent);
}

bool WebView::keyDown(_mc_key_sym key, unsigned m)
{
	PlatformKeyboardEvent keyEvent(true, (unsigned)key, m);
	Frame* frame = d->m_frame->page()->focusController()->focusedOrMainFrame();
	return frame->eventHandler()->keyEvent(keyEvent);
}

bool WebView::contextMenu(unsigned m, int x, int y)
{
    d->m_frame->page()->contextMenuController()->clearContextMenu();
	IntPoint p(x, y);
	PlatformMouseEvent mouseEvent(MouseEventPressed, _get_mouse_button(MOUSE_BTN_RIGHT), p, m);
    Frame* focusedFrame = d->m_frame->page()->focusController()->focusedOrMainFrame();
	if (cb_set_cursor)
		cb_set_cursor(POINTER_CURSOR);

    bool handledEvent = focusedFrame->eventHandler()->sendContextMenuEvent(mouseEvent);
	if (handledEvent) {
		return true;
	}
	return false;
}

void WebView::setFocus(void)
{
    ChromeClientMC * client = static_cast<ChromeClientMC *>(d->m_frame->page()->chrome()->client());
	if (!client->isFocused()) {
    	Frame* frame = d->m_frame->page()->focusController()->focusedOrMainFrame();
    	d->m_frame->page()->focusController()->setFocusedFrame(frame);
    	client->setFocused(true);
	}
}

void WebView::killFocus(void)
{
    ChromeClientMC * client = static_cast<ChromeClientMC *>(d->m_frame->page()->chrome()->client());
	if (client->isFocused()) {
    	d->m_frame->page()->focusController()->setFocusedFrame(0);
    	client->setFocused(false);
	}
}

int WebView::renderMode(void)
{
	return d->m_mode;
}

void WebView::setRenderMode(int mode, int limit)
{
	d->m_mode = mode;
	switch (mode)
	{
	case 0:
		{
			d->m_frameView->setNeedsLayout();
			d->m_frame->page()->setSmallView(false);
		}
		break;
	case 1:
		{
			d->m_frameView->setNeedsLayout();
			d->m_frame->page()->setSmallView(true);
            d->m_frame->page()->setSmallViewWidth((unsigned)limit);
		}
		break;
	}
	reflow();
}

void WebView::setViewSource(bool b)
{
    d->m_frame->setInViewSourceMode(b);
}

void WebView::setContentsPosition(int x, int y)
{
	int dx, dy, fx, fy, max_x, max_y;

	Frame* focus = d->m_frame->page()->focusController()->focusedOrMainFrame();
	dx = x - focus->view()->contentsX();
	dy = y - focus->view()->contentsY();

	for (Frame *frame = focus; frame; frame = frame->tree()->parent()) {
		fx = dx + frame->view()->contentsX();
		fy = dy + frame->view()->contentsY();

		max_x = frame->view()->contentsWidth();
		max_y = frame->view()->contentsHeight();

		if (fx > max_x) fx = max_x;
		if (fy > max_y) fy = max_y;
		if (fx < 0) fx = 0;
		if (fy < 0) fy = 0;

		if (frame->view()->setContentsPos(fx, fy))
			break;
	}
}

void WebView::contentsPosition(int *x, int *y)
{
    if (!x || !y)
        return;

	Frame* frame = d->m_frame->page()->focusController()->focusedOrMainFrame();
	*x = frame->view()->contentsX();
	*y = frame->view()->contentsY();
}

_mc_size WebView::contentsSize(void)
{
	_mc_size size;
	Frame* frame = d->m_frame->page()->focusController()->focusedOrMainFrame();
	size.w = frame->view()->contentsWidth();
    size.h = frame->view()->contentsHeight();
	return size;
}

void WebView::backward(void)
{
    d->m_frame->page()->goBack();
	garbageRelease();
}

void WebView::forward(void)
{
    d->m_frame->page()->goForward();
	garbageRelease();
}

void WebView::stop(void)
{
    d->m_frame->loader()->stopForUserCancel();
	garbageRelease();
}

void WebView::reload(void)
{
    d->m_frame->loader()->reload();
	garbageRelease();
}

void WebView::repaint(void)
{
	IntRect rc = IntRect(d->m_frame->view()->visibleContentRect());
	d->m_frame->view()->updateContents(rc, true);
    for (Frame* child = d->m_frame->tree()->firstChild(); child; child = child->tree()->nextSibling()){
		IntRect crc = IntRect(child->view()->visibleContentRect());
		child->view()->updateContents(crc, true);
	}
}

void WebView::reflow(void)
{
    if (d->m_frame->document())
        d->m_frame->document()->recalcStyle(Node::Force);
    for (Frame* child = d->m_frame->tree()->firstChild(); child; child = child->tree()->nextSibling()){
        if (child->document())
            child->document()->recalcStyle(Node::Force);
	}

    d->m_frameView->layoutIfNeededRecursive();
}

void WebView::loadHtml(const char* str, const char* rurl)
{
    stop();
	String urlstr = String::fromUTF8(rurl);
	KURL baseurl(urlstr.deprecatedString());
    ResourceRequest request(baseurl);
    RefPtr<WebCore::SharedBuffer> data = new SharedBuffer(str, strlen(str));
    SubstituteData substituteData(data, String("text/html"), String("utf-8"), KURL());
    d->m_frame->loader()->load(request, substituteData);
}

void WebView::loadUrl(const char* url, bool lc)
{	
    stop();
    if (0 == strncasecmp(url, "about:blank", 11)) {
        if (cb_set_location)
            cb_set_location(d->m_view, url);

        if (cb_set_title)
            cb_set_title(d->m_view, url);

        return;
    }

	KURL Url;
	if (0 == strncasecmp(url, "file://", 7)) {
		DeprecatedString UrlStr = KURL::encode_string(DeprecatedString::fromUtf8(url));
		Url = KURL(UrlStr);
	} else {
		Url = KURL(url);
	}

    if (!Url.isValid()){ 
        //try to guess it is a http url.
        DeprecatedString urlstr("http://");
        urlstr.append(url);
        Url = KURL(urlstr);
    }

    if (!Url.isValid())// it is still a invalid url! 
        return;

#if ENABLE(SCHEMEEXTENSION)
    if (scheduleScheme(Url))
        return;
#endif

    ResourceRequest request(Url);
    d->m_frame->page()->backForwardList()->setEnabled(!lc);
    d->m_frame->loader()->load(request);
}

bool WebView::textInput(const char* text)
{
	String str = String::fromUTF8(text);
	if (str.isEmpty() || str.isNull())
		return false;

    Editor * editor = d->m_frame->page()->focusController()->focusedOrMainFrame()->editor();
	if (!editor->canEdit()) 
		return false;

    editor->confirmComposition(str);
	return true;
}

void WebView::setEncodingName(_mc_encoding name)
{
    if (name == CHARSET_AUTO_DETECT)
        d->m_frame->loader()->documentLoader()->setOverrideEncoding(""); //auto detect
    else
        d->m_frame->loader()->documentLoader()->setOverrideEncoding(String(Encodings[name]));

    reload();
}

_mc_encoding WebView::encodingName(void)
{
    String encoding = d->m_frame->loader()->documentLoader()->overrideEncoding();
    if (!encoding.isEmpty()) {
        for (int i = 0; i < EncodingNum; i++) {
            if (equalIgnoringCase(encoding, Encodings[i]))
                return static_cast<MC_ENCODING_NAME>(i);
        }
    }
    return CHARSET_AUTO_DETECT;
}

int WebView::textScale(void)
{
    return d->m_frame->zoomFactor();
}

void WebView::setTextScale(int factor)
{
    d->m_frame->setZoomFactor(factor);
}

int WebView::scaleFactor(void)
{
	return (int)(d->m_frame->pageZoomFactor()*100);
}

void WebView::setScaleFactor(int scale)
{
	if (scale < 10) scale = 10;
	if (scale > 500) scale = 500;

	if (d->m_frame->setPageZoomFactor((float)scale/100.0f))
		firstLayout();
}

bool WebView::search(const char *str, bool forward, bool caseSens, bool wrap)
{
    if (!d->m_frame->page() || !d->m_frame->page()->mainFrame())
        return false;

    if (!str || !strlen(str))
        return false;

    String search(str, strlen(str));
    bool found = false;

    Frame* frame = d->m_frame->page()->focusController()->focusedOrMainFrame();
    Frame* startFrame = frame;
    do {
        found = frame->findString(search, forward, caseSens, false, true);
        if (found) {
            if (frame != startFrame)
                startFrame->selectionController()->clear();
            d->m_frame->page()->focusController()->setFocusedFrame(frame);
            return found;
        }
        frame = incrementFrame(frame, forward, wrap);
    } while (frame && frame != startFrame);

    // Search contents of startFrame, on the other side of the selection that we did earlier.
    // We cheat a bit and just research with wrap on
    if (wrap && !startFrame->selectionController()->isNone()) {
        found = startFrame->findString(search, forward, caseSens, true, true);
        d->m_frame->page()->focusController()->setFocusedFrame(frame);
    }

    return found;
}

int WebView::markAll(const char *str, bool caseSens, bool highlight, unsigned int limit)
{
    if (!d->m_frame->page() || !d->m_frame->page()->mainFrame())
        return -1;

    if (!str || !strlen(str))
        return -1;

    String search(str, strlen(str));
    unsigned int matches = 0;

    Frame* frame = d->m_frame->page()->mainFrame();
    do {
        frame->setMarkedTextMatchesAreHighlighted(highlight);
        matches += frame->markAllMatchesForText(search, caseSens, (limit == 0)? 0 : (limit - matches));
        frame = incrementFrame(frame, true, false);
    } while (frame);

    return matches;
}

void WebView::executeScript(const char* script)
{
	d->m_frame->loader()->executeScript(String::fromUTF8(script), true);
}

void WebView::unmarkAll(void)
{
    if (!d->m_frame->page() || !d->m_frame->page()->mainFrame())
        return;

    Frame* frame = d->m_frame->page()->mainFrame();
    do {
        if (Document* document = frame->document())
            document->removeMarkers(DocumentMarker::TextMatch);
        frame = incrementFrame(frame, true, false);
    } while (frame);
}

void WebView::firstLayout(void)
{
	if (!d->m_minLayoutSize.isEmpty()) { //use min layout size.
		d->m_frameView->resize(d->m_minLayoutSize.width(), d->m_minLayoutSize.height());
		d->m_oldLayoutSize = IntSize(0, 0);
	}
}

void WebView::resizeContents(int w, int h)
{
	if (!d->m_minLayoutSize.isEmpty()) { //use min layout size.
		if (w && h) {
			int sw = min(max(d->m_minLayoutSize.width(), w), d->m_width);
			int sh = min(max(d->m_minLayoutSize.height(), h), d->m_height);

			if (((d->m_oldLayoutSize.width() < sw) || (d->m_oldLayoutSize.height() < sh))) {

				int nw = d->m_oldLayoutSize.width();
				int nh = d->m_oldLayoutSize.height();

				// FIXME: default margin 8 px
				nw = (8 > (sw-nw) && nw > 0) ? nw : sw;
				nh = (8 > (sh-nh) && nh > 0) ? nh : sh;

				d->m_frameView->resize(nw, nh);
				d->m_oldLayoutSize = IntSize(nw, nh);
			}
		}
	}
}

bool WebView::isTextAntialias(void)
{
	Settings* setting = Settings::globalSettings();
	return setting->textAntialias();
}

void WebView::setTextAntialias(bool b)
{
	Settings* setting = Settings::globalSettings();
	setting->setTextAntialias(b);
}

MouseButton _get_mouse_button(_mc_mouse_btn button)
{
	switch (button) {
		case MOUSE_BTN_LEFT:
			return LeftButton;
		case MOUSE_BTN_MIDDLE:
			return MiddleButton;
		case MOUSE_BTN_RIGHT:
			return RightButton;
		default:
			return NoButton;
	}
}
}
