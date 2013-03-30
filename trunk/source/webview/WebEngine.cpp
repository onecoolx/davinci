/*
** webengine.cpp: webengine implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include <picasso.h>
#include "macross.h"

#include "SharedTimer.h"
#include <wtf/FastMalloc.h>

#include "KURL.h"
#include "ResourceHandle.h"
#include "ResourceRequest.h"
#include "FrameLoader.h"
#include "ProxyPlatform.h"
#include "CookieManager.h"
#include "CacheManager.h"
#include "GraphicsContext.h"
#include "PlatformScrollBar.h"
#include "PopupMenu.h"
#include "WebView.h"
#include "Settings.h"
#include "CookieJar.h"
#include "WebEngine.h"
#include "WebEncoding.h"
#include "WebCallback.h"
#include "Language.h"
#include "SchemeExtension.h"
#include "NativeBinding.h"
#include "CertificateMC.h"
#include "GCController.h"
#include "Cache.h"

namespace WebCore {
extern void setPixelFormat(_mc_format format);
extern void setScreenSize(int w, int h);
extern ps_color_format pixelFormat(void);
extern void globalDataSave(void);
}

using namespace WTF;
using namespace WebCore;
using namespace MaCross;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// webview functions
MaCrossView* macross_view_create(MC_BYTE* buffer, int width, int height, int pitch, void *user_data)
{
	if (!buffer || width <= 0 || height <= 0)
		return 0;

	MaCrossView * p = (MaCrossView*)fastMalloc(sizeof(MaCrossView));
	memset(p, 0, sizeof(MaCrossView));
	if (p) {
		p->view = new WebView(p, buffer, width, height, pitch);
		p->data = user_data;
		return p;
	} else
		return 0;
}

void* macross_view_additional_data(MaCrossView* view)
{
	if (!view)
		return 0;

	return view->data;
}

MC_STATUS macross_view_destroy(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	delete view->view;
	fastFree(view);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_update(MaCrossView* view, const MC_RECT* rc)
{
	if (!view)
		return MC_STATUS_FAILED;

	if (rc) {
		view->view->setDirtyRect(rc->x, rc->y, rc->w, rc->h);
	}
	view->view->paintView();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_resize(MaCrossView* view, MC_BYTE* buffer, int width, int height, int pitch)
{
	if (!view || !buffer || width <= 0 || height <= 0)
		return MC_STATUS_FAILED;

	view->view->resizeView(buffer, width, height, pitch);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_set_minimum_layout_size(MaCrossView* view, const MC_SIZE *size)
{
	if (!view)
		return MC_STATUS_FAILED;

	if (size && size->w && size->h) 
		view->view->setMinLayoutSize(size->w, size->h);
	else 
		view->view->clearMinLayoutSize();

	return MC_STATUS_SUCCESS;
}


MC_STATUS macross_set_callback(const MC_CALLBACK_INFO* info)
{
	if (!info)
		return MC_STATUS_FAILED;

	_set_callback(info);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_keyboard_event(MaCrossView* view, const MC_KEY_EVENT *event)
{
	if (!view || !event)
		return MC_STATUS_FAILED;

	bool ret = false;
	switch(event->type) {
	case EVT_KEY_UP:
		{
			ret = view->view->keyUp(event->key, event->modifier);
		}
		break;
	case EVT_KEY_DOWN:
		{
			ret = view->view->keyDown(event->key, event->modifier);
		}
		break;
	}

	if (ret)
		return MC_STATUS_SUCCESS;
	else
		return MC_STATUS_FAILED;
}

MC_STATUS macross_mouse_event(MaCrossView* view, const MC_MOUSE_EVENT *event) 
{
	if (!view || !event)
		return MC_STATUS_FAILED;

	bool ret = false;
	switch (event->type) {
	case EVT_MOUSE_UP:
		{
			ret = view->view->mouseUp(event->button, event->modifier, event->point.x, event->point.y);
		}
		break;
	case EVT_MOUSE_DOWN:
		{
			ret = view->view->mouseDown(event->button, event->modifier, event->point.x, event->point.y);
		}
		break;
	case EVT_MOUSE_MOVE:
		{
			ret = view->view->mouseMove(event->button, event->modifier, event->point.x, event->point.y);
		}
		break;
	case EVT_MOUSE_WHEEL:
		{
			ret = view->view->mouseWheel(event->button, event->modifier, event->point.x, event->point.y);
		}
		break;
	}

	if (ret)
		return MC_STATUS_SUCCESS;
	else
		return MC_STATUS_FAILED;
}

MC_STATUS macross_context_menu_event(MaCrossView* view, const MC_CONTEXT_EVENT *event)
{
	if (!view || !event)
		return MC_STATUS_FAILED;

	bool ret = view->view->contextMenu(event->modifier, event->point.x, event->point.y);
	
	if (ret)
		return MC_STATUS_SUCCESS;
	else
		return MC_STATUS_FAILED;
}

MC_STATUS macross_view_set_focus(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->setFocus();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_kill_focus(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->killFocus();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_input_text(MaCrossView* view, const char* text)
{
	if (!view || !text)
		return MC_STATUS_FAILED;

	if (view->view->textInput(text))
		return MC_STATUS_SUCCESS;
	else
		return MC_STATUS_FAILED;
}

MC_STATUS macross_view_set_encoding(MaCrossView* view, MC_ENCODING_NAME encoding)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->setEncodingName(encoding);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_get_encoding(MaCrossView* view, MC_ENCODING_NAME* encoding)
{
	if (!view || !encoding)
		return MC_STATUS_FAILED;

	*encoding = view->view->encodingName();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_set_rendering_mode(MaCrossView* view, MC_RENDERING_MODE mode, int space)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->setRenderMode(mode, space);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_get_rendering_mode(MaCrossView* view, MC_RENDERING_MODE* mode)
{
	if (!view || !mode)
		return MC_STATUS_FAILED;

	*mode = (MC_RENDERING_MODE)view->view->renderMode();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_set_scale_factor(MaCrossView* view, int scale)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->setScaleFactor(scale);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_get_scale_factor(MaCrossView* view, int* scale)
{
	if (!view || !scale)
		return MC_STATUS_FAILED;

	*scale = view->view->scaleFactor();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_set_view_source(MaCrossView* view, MC_BOOL enable)
{
	if (!view)
		return MC_STATUS_FAILED;

    view->view->setViewSource((enable ? true : false));
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_set_position(MaCrossView* view, int x, int y)
{
	if (!view)
		return MC_STATUS_FAILED;

    view->view->setContentsPosition(x, y);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_get_position(MaCrossView* view, int* x, int* y)
{
	if (!view || !x || !y)
		return MC_STATUS_FAILED;

    view->view->contentsPosition(x, y);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_load_html(MaCrossView* view, const char* htmlstr, const char* url)
{
	if (!view || !htmlstr)
		return MC_STATUS_FAILED;

	view->view->loadHtml(htmlstr, url);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_open_url(MaCrossView* view, const char* url)
{
	if (!view || !url)
		return MC_STATUS_FAILED;

	view->view->loadUrl(url, false);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_get_contents_size(MaCrossView* view, MC_SIZE* size)
{
	if (!view || !size)
		return MC_STATUS_FAILED;

    *size = view->view->contentsSize();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_open_url_quietly(MaCrossView* view, const char* url)
{
	if (!view || !url)
		return MC_STATUS_FAILED;

	view->view->loadUrl(url, true);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_forward(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->forward();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_backward(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->backward();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_stop(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->stop();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_reload(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->reload();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_reflow(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->reflow();
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_view_repaint(MaCrossView* view)
{
	if (!view)
		return MC_STATUS_FAILED;

	view->view->repaint();
	return MC_STATUS_SUCCESS;
}

MC_BOOL macross_view_search_text(MaCrossView* view, const char* str, 
													MC_BOOL forward, MC_BOOL caseSen, MC_BOOL wrap)
{
    if (!view || !str)
        return FALSE;

    return view->view->search(str, forward, (caseSen ? true : false), 
												(wrap ? true : false)) ? TRUE : FALSE;
}

int macross_view_mark_all_matches_text(MaCrossView* view, const char *str, 
													MC_BOOL caseSen, MC_BOOL high, unsigned int limit)
{
    if (!view || !str)
        return -1;

   return view->view->markAll(str, (caseSen ? true : false), (high ? true : false), limit);
}

MC_BOOL macross_view_unmark_all_matches(MaCrossView* view)
{
    if (!view)
        return FALSE;

    view->view->unmarkAll();
    return TRUE;
}

MC_BOOL macross_view_get_text_multiplier(MaCrossView* view, int *factor)
{
    if (!view || !factor)
        return FALSE;

    *factor = view->view->textScale();
    return TRUE;
}

MC_BOOL macross_view_set_text_multiplier(MaCrossView* view, int factor)
{
    if (!view)
        return FALSE;

    view->view->setTextScale(factor);
    return TRUE;
}

MC_BOOL macross_view_eval_script(MaCrossView* view, const char* script)
{
    if (!view)
        return FALSE;

    view->view->executeScript(script);
    return TRUE;
}

MC_STATUS macross_menu_resize(MC_POPUP_MENU* menu, int width, int height)
{
	if (!menu || width <= 0 || height <= 0)
		return MC_STATUS_FAILED;

    PopupMenu * popup = (PopupMenu *)menu->handle;
    if (popup && popup->scrollBar()) {
		IntSize size(width, height);
		popup->scrollBar()->setRect(IntRect(size.width() - popup->scrollBar()->width(), 0,
					popup->scrollBar()->width(), size.height()));
		int visibleItems = popup->visibleItems();
		popup->scrollBar()->setEnabled(visibleItems < popup->client()->listSize());
		popup->scrollBar()->setSteps(1, max(1, visibleItems - 1));
		popup->scrollBar()->setProportion(visibleItems, popup->client()->listSize());
	}
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_menu_update(MC_POPUP_MENU* menu, const MC_RECT* rect)
{
	if (!menu)
		return MC_STATUS_FAILED;

    Settings *settings = Settings::globalSettings();
	ps_canvas * canvas = ps_canvas_create_with_data(menu->buffer, pixelFormat(), 
										menu->rect.w, menu->rect.h, menu->pitch);
	ps_context* context = ps_context_create(canvas, 0);
	ps_set_text_antialias(context, settings->textAntialias() ? True : False);
	GraphicsContext gc(context);
    PopupMenu * popup = (PopupMenu *)menu->handle;
    if (popup) {
		IntRect crt = popup->clientRect();
		if (rect) {
			IntRect brt(rect->x, rect->y, rect->w, rect->h);
			crt.unite(brt);
		}
    	popup->paint(crt, &gc);
	}
	ps_context_unref(context);
	ps_canvas_unref(canvas);
	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_menu_hide(MC_POPUP_MENU* menu)
{
	if (!menu)
		return MC_STATUS_FAILED;

    PopupMenu * popup = (PopupMenu *)menu->handle;
	if (popup && popup->client())
		popup->client()->hidePopup();

	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_menu_keyboard_event(MC_POPUP_MENU* menu, const MC_KEY_EVENT* event)
{
	if (!menu || !event)
		return MC_STATUS_FAILED;

	PopupMenu * popup = (PopupMenu *)menu->handle;
	if (popup && popup->client() && (event->type == EVT_KEY_DOWN)) {
		switch (event->key) {
			case KEY_UP:
				popup->up();
				break;
			case KEY_DOWN:
				popup->down();
				break;
			case KEY_HOME:
				popup->focusFirst();
				break;
			case KEY_END:
				popup->focusLast();
				break;
			case KEY_PAGEUP:
				{
					if (popup->focusedIndex() != popup->scrollOffset()) {
						int firstVisibleItem = popup->scrollOffset();
						popup->up(popup->focusedIndex() - firstVisibleItem);
					} else
						popup->up(popup->visibleItems());
				}
				break;
			case KEY_PAGEDOWN:
				{
					int lastVisibleItem = popup->scrollOffset() + popup->visibleItems() - 1;
					if (popup->focusedIndex() != lastVisibleItem) {
						popup->down(lastVisibleItem - popup->focusedIndex());
					} else
						popup->down(popup->visibleItems());
				}
				break;
			case KEY_ENTER:
				{
					popup->client()->hidePopup();
					int index = popup->focusedIndex();
					popup->client()->valueChanged(index);
				}
				break;
			case KEY_ESCAPE:
				popup->client()->hidePopup();
				break;
			default:
				break;
		}
	}

	return MC_STATUS_SUCCESS;
}

MC_STATUS macross_menu_mouse_event(MC_POPUP_MENU* menu, const MC_MOUSE_EVENT* event)
{
	if (!menu || !event)
		return MC_STATUS_FAILED;

    PopupMenu * popup = (PopupMenu *)menu->handle;
    if (popup) {
		switch (event->type) {
			case EVT_MOUSE_MOVE:
				{
					IntPoint mousePoint(event->point.x, event->point.y);
					if (popup->scrollBar()) {
						IntRect scrollBarRect = popup->scrollBar()->frameGeometry();
						if (popup->scrollbarCapturingMouse() || scrollBarRect.contains(mousePoint)) {
                        // Put the point into coordinates relative to the scroll bar
                        	mousePoint.move(-scrollBarRect.x(), -scrollBarRect.y());
                        	PlatformMouseEvent mevent(MouseEventMoved, 
										_get_mouse_button(event->button), mousePoint, event->modifier);
                        	popup->scrollBar()->handleMouseMoveEvent(mevent);
							break;
						}
                    }

					IntRect bounds = popup->windowClientRect();
					if (bounds.contains(mousePoint.x(), mousePoint.y())){
						popup->setFocusedIndex(popup->listIndexAtPoint(mousePoint), true);
					}
				}
				break;
			case EVT_MOUSE_UP:
				{
					IntPoint mousePoint(event->point.x, event->point.y);
					if (popup->scrollBar()) {
						IntRect scrollBarRect = popup->scrollBar()->frameGeometry();
						if (popup->scrollbarCapturingMouse() || scrollBarRect.contains(mousePoint)) {
							popup->setScrollbarCapturingMouse(false);
							// Put the point into coordinates relative to the scroll bar
							mousePoint.move(-scrollBarRect.x(), -scrollBarRect.y());
							PlatformMouseEvent mevent(MouseEventReleased, 
										_get_mouse_button(event->button), mousePoint, event->modifier);
							popup->scrollBar()->handleMouseReleaseEvent(mevent);
							// FIXME: This is a hack to work around PlatformScrollbar not 
							// invalidating correctly when it doesn't have a parent widget
							IntRect r = scrollBarRect;
							popup->updateRect(r.x(), r.y(), r.width(), r.height());
							break;
						}
					}
					IntRect bounds = popup->windowClientRect();
					if (popup->client() && bounds.contains(mousePoint.x(), mousePoint.y())) {
						popup->client()->hidePopup();
						int index = popup->focusedIndex();
						if (index >= 0)
							popup->client()->valueChanged(index);
					}
				}
				break;
			case EVT_MOUSE_DOWN:
				{
					IntPoint mousePoint(event->point.x, event->point.y);
					if (popup->scrollBar()) {
						IntRect scrollBarRect = popup->scrollBar()->frameGeometry();
						if (scrollBarRect.contains(mousePoint)) {
							// Put the point into coordinates relative to the scroll bar
							mousePoint.move(-scrollBarRect.x(), -scrollBarRect.y());
							PlatformMouseEvent mevent(MouseEventPressed,
										_get_mouse_button(event->button), mousePoint, event->modifier);
							popup->scrollBar()->handleMousePressEvent(mevent);
							popup->setScrollbarCapturingMouse(true);
							break;
						}
					}

					IntRect bounds = popup->windowClientRect();
					if (popup->client() && bounds.contains(mousePoint.x(), mousePoint.y())) {
						popup->setFocusedIndex(popup->listIndexAtPoint(mousePoint), true);
					} else {
						popup->client()->hidePopup();
					}
				}
				break;
			default:
				break;
		}
	}
	return MC_STATUS_SUCCESS;
}

#if ENABLE(SSLFILE)
MC_BOOL macross_set_certificate_dir(const char * path)
{
    if(!path)
        return FALSE;

    WebCore::CString _path(path, strlen(path));
    WebCore::setCaPath(_path);
    return TRUE;   
}
#endif

MC_BOOL macross_set_proxy(const MC_PROXY *p)
{
	if (!p) {
		setProxyEnabled(false);
		return TRUE;
	}
	
	if (!p->Host || !p->Port || !p->UserName || !p->PassWord) 
		return FALSE;

	int type = (int)p->Type;
	if (type < 0 || type > 2)
		return FALSE;

	setProxyEnabled(true);

	ProxyItem item(p->UserName, p->PassWord, p->Host, p->Port, (int)p->Type);

    setProxy(item);
	return TRUE;
}

MC_BOOL macross_set_config(const MC_CONFIG *config)
{
	if (!config)
		return FALSE;

    Settings *settings = Settings::globalSettings();

	setDefaultLanguage(config->language);
    settings->setStandardFontFamily(AtomicString(config->std_font));
    settings->setFixedFontFamily(AtomicString(config->fixed_font));
    settings->setSerifFontFamily(AtomicString(config->serif_font));
    settings->setSansSerifFontFamily(AtomicString(config->sans_serif_font));
	if (config->default_encoding != -1)
    	settings->setDefaultTextEncodingName(String(Encodings[config->default_encoding]));
    settings->setDefaultFontSize(config->fontsize);
    settings->setDefaultFixedFontSize(config->fixed_fontsize);
	settings->setScrollBarWidth(config->scrollbar_width);
    settings->setLoadsImagesAutomatically(config->autoload_images == TRUE);
    settings->setAutoDetectEncoding(config->autodetect_encoding == TRUE);
    settings->setJavaScriptEnabled(config->enable_javascript==TRUE);
    settings->setPluginsEnabled(config->enable_plugin == TRUE);
    setCookiesEnabled(config->enable_cookies == TRUE);
    settings->setJavaScriptCanOpenWindowsAutomatically(config->block_popup == FALSE);
    settings->setShowAllAtOnce(config->show_at_once == TRUE);
	settings->setTextAntialias(config->text_antialias == TRUE);

	return TRUE;
}

MC_BOOL macross_get_config(MC_CONFIG *config)
{
	if (!config)
		return FALSE;

    Settings *settings = Settings::globalSettings();

    strncpy(config->language, defaultLanguage().latin1().data(), FIELD_MAX);
    strncpy(config->std_font, settings->standardFontFamily().domString().latin1().data(), FIELD_MAX);
    strncpy(config->serif_font, settings->serifFontFamily().domString().latin1().data(), FIELD_MAX);
    strncpy(config->fixed_font, settings->fixedFontFamily().domString().latin1().data(), FIELD_MAX);
    strncpy(config->sans_serif_font,settings->sansSerifFontFamily().domString().latin1().data(),FIELD_MAX);
    config->fontsize = settings->defaultFontSize();
    config->fixed_fontsize = settings->defaultFixedFontSize();
	config->scrollbar_width = settings->scrollBarWidth();

    for (int i = 0; i < EncodingNum; i++) {
        if (strcmp(Encodings[i], settings->defaultTextEncodingName().latin1().data()) == 0){
    		config->default_encoding = (MC_ENCODING_NAME)i;
            break;
		}
    }
    config->autoload_images = settings->loadsImagesAutomatically() ? TRUE : FALSE;
    config->autodetect_encoding = settings->autoDetectEncoding();
    config->enable_javascript = settings->isJavaScriptEnabled() ? TRUE : FALSE;
    config->enable_cookies = cookiesEnabled() ? TRUE : FALSE;
    config->enable_plugin = settings->arePluginsEnabled() ? TRUE : FALSE;
    config->block_popup= settings->JavaScriptCanOpenWindowsAutomatically() ? FALSE: TRUE;
    config->show_at_once = settings->showAllAtOnce() ? TRUE : FALSE;
	config->text_antialias = settings->textAntialias() ? TRUE : FALSE;

	return TRUE;
}

MC_STATUS macross_shrink_cache_memory(void)
{
	if (!cache()->disabled()){
		cache()->prune();
		WebCore::gcController().garbageCollectSoon();
		return MC_STATUS_SUCCESS;
	} else
		return MC_STATUS_FAILED;
}

unsigned long macross_get_cache_memory_size(void)
{
	if (!cache()->disabled()){
		return cache()->getSize();
	} else
		return 0;
}

unsigned long macross_set_disk_cache_size(unsigned long size)
{
	unsigned long old = (unsigned long)CacheManager::sharedInstance()->getCacheMaxSize();
	if (size)
		CacheManager::sharedInstance()->setCacheMaxSize((size_t)size);
	return old;
}

MC_STATUS macross_clear_disk_cache(void)
{
	if (CacheManager::sharedInstance()->freeAllItems())
		return MC_STATUS_SUCCESS;
	else
		return MC_STATUS_FAILED;
}

MC_STATUS macross_clear_cookies(void)
{
	if (CookieManager::sharedInstance()->removeAll())
		return MC_STATUS_SUCCESS;
	else
		return MC_STATUS_FAILED;
}

MC_RESPONSE macross_network_request(MC_REQUEST_TYPE type, const char* url, cb_network_callback f, unsigned int t)
{
	KURL rurl(url);
	if (!rurl.isValid())
		return RESPONSE_INVALID_URL;

	ResourceRequest request(rurl);
	request.setHTTPUserAgent(composeUserAgent());
	request.setTimeoutInterval((t < 5) ? 5 : ((t > 300) ? 300 : t));
	if (type == REQUEST_POST) {
		request.setHTTPMethod("POST");
		if (!rurl.query().isEmpty()) {
			request.setHTTPBody(new FormData(rurl.query().utf8()));
		}
	}

	if (request.isEmpty() || request.isNull())
		return RESPONSE_INVALID_URL;

	ResourceResponse response;
	ResourceError error;
	Vector<char> data;
	ResourceHandle::loadResourceSynchronously(request, error, response, data);

	if (f && !data.isEmpty()){
		f(response.httpStatusCode(), (unsigned char*)data.data(), data.size(), TRUE);
	}

	if (response.httpStatusCode() == 200)
		return RESPONSE_OK;
	else
		return RESPONSE_ERROR;
}

#if ENABLE(JSNATIVEBINDING)
MC_BOOL macross_js_define_class(JSNativeClass *cls)
{
    return DefineJSNativeClass(cls) ? TRUE : FALSE;
}

MC_BOOL macross_js_undefine_class(JSNativeClass *cls)
{
    return UndefineJSNativeClass(cls) ? TRUE : FALSE;
}

const JSClassRef macross_js_lookup_class(const char* name)
{
    return LookupJSNativeClass(name);
}

MC_BOOL macross_js_define_function(JSNativeFunction *func)
{
    return DefineJSNativeFunction(func) ? TRUE : FALSE;
}

MC_BOOL macorss_js_undefine_function(JSNativeFunction *func)
{
    return UndefineJSNativeFunction(func) ? TRUE : FALSE;
}
#endif /* ENABLE(JSNATIVEBINDING) */

#if ENABLE(SCHEMEEXTENSION)
MC_BOOL macross_register_scheme(const char * scheme, cb_scheme_callback cb, void* data)
{
    return RegisterSchemeHandler(scheme, cb, data) ? TRUE : FALSE;
}

MC_BOOL macross_unregister_scheme(const char* scheme)
{
    return UnregisterSchemeHandler(scheme) ? TRUE : FALSE;
}
#endif

// global functions
static bool g_initialize = false;

MC_STATUS macross_initialize(MC_PIXEL_FORMAT format, int w, int h)
{
	if (!g_initialize || w <=0 || h <= 0) {
		if (!ps_initialize())
			return MC_STATUS_FAILED;

		WebCore::setPixelFormat(format);	
		WebCore::setScreenSize(w, h);
		WebCore::eventInitialize();
		
		_init_callback();
		g_initialize = true;
	}
	return MC_STATUS_SUCCESS;
}

void macross_shutdown(void)
{
	if (g_initialize) {
		WebCore::eventShatdown();
		globalDataSave();
		ps_shutdown();
		g_initialize = false;
	}
}

void macross_event_dispatch(void)
{
	if (g_initialize) {
		WebCore::eventDispatch();
	}
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
