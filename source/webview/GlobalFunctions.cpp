/*
** GlobalFunctions.cpp: GlobalFunctions implements
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"

#include "AXObjectCache.h"
#include "CachedResource.h"
#include "ContextMenu.h"
#include "CookieJar.h"
#include "CString.h"
#include "Cursor.h"
#include "DocumentLoader.h"
#include "EventHandler.h"
#include "FileChooser.h"
#include "Font.h"
#include "FrameLoader.h"
#include "FrameLoadRequest.h"
#include "FrameView.h"
#include "Frame.h"
#include "GraphicsContext.h"
#include "History.h"
#include "IntPoint.h"
#include "KURL.h"
#include "Language.h"
#include "loader.h"
#include "Node.h"
#include "Page.h"
#include "CachedPage.h"
#include "CacheManager.h"
#include "ResourceHandleManager.h"
#include "Path.h"
#include "PlatformMouseEvent.h"
#include "PlatformString.h"
#include "PlatformScrollBar.h"
#include "PopupMenu.h"
#include "RenderTheme.h"
#include "ResourceLoader.h"
#include "RenderThemePS.h"
#include "Screen.h"
#include "ScrollBar.h"
#include "TextBoundaries.h"
#include "Widget.h"
#include "Debug.h"

#include "WebCallback.h"

#include "macross.h"
#include <picasso.h>

using namespace WebCore;
using namespace MaCross;

namespace WebCore {

static String g_defaultLanguage = "en";
String defaultLanguage()
{
    return g_defaultLanguage;
}

void setDefaultLanguage(const String & languaqge)
{
    g_defaultLanguage = languaqge;
}

bool historyContains(DeprecatedString const& url) 
{
    if (cb_url_is_visited) {
        if (cb_url_is_visited(url.utf8().data()))
            return true;
	}
    return false;
}

static int g_screen_width;
static int g_screen_height;

void setScreenSize(int w, int h)
{
	g_screen_width = w;
	g_screen_height = h;
}

int screenWidth(void)
{
	return g_screen_width;
}

int screenHeight(void)
{
	return g_screen_height;
}

static ps_color_format g_pixel_format;
void setPixelFormat(_mc_format format)
{
	switch (format) {
		case PIXEL_FORMAT_BGRA32:
			g_pixel_format = COLOR_FORMAT_BGRA;
			break;
		case PIXEL_FORMAT_BGR24:
			g_pixel_format = COLOR_FORMAT_BGR;
			break;
		case PIXEL_FORMAT_RGB16:
			g_pixel_format = COLOR_FORMAT_RGB565;
			break;
	}
}

ps_color_format pixelFormat(void)
{
	return g_pixel_format;
}

int pixelPerBytes(void)
{
	switch(g_pixel_format) {
		case COLOR_FORMAT_BGRA:
			return 4;
		case COLOR_FORMAT_BGR:
			return 3;
		case COLOR_FORMAT_RGB565:
			return 2;
		default:
			return 0;
	}
}


static ps_context* g_context = 0;
static ps_canvas* g_canvas = 0;

static bool context_init = false;
static void global_context_init(void)
{
	g_canvas = ps_canvas_create(g_pixel_format, 10, 10);
	g_context = ps_context_create(g_canvas, 0);
	context_init = true;
}

ps_context* getGlobalContext(void)
{
	if (!context_init)
		global_context_init();

	return g_context;
}

void globalDataSave(void)
{
	ResourceHandleManager::releaseAllResourceJobs();
#if ENABLE(HTTPCACHE)
	CacheManager::saveAndReleaseAllCacheItems();
#endif
}



//not implements functions.
String signedPublicKeyAndChallengeString(unsigned keySizeIndex, const String &challengeString, const KURL &url) { return String(); }
Vector<String> supportedKeySizes() { notImplemented(); return Vector<String>(); }


Color focusRingColor() { notImplemented(); return 0xFF0000FF; }
void setFocusRingColorChangeFunction(void (*)()) { notImplemented(); }

int findNextWordFromIndex(UChar const*, int, int, bool) { notImplemented(); return 0; }
void findWordBoundary(UChar const* str, int len, int position, int* start, int* end) { notImplemented(); *start = position; *end = position; }

void CachedPage::close() { notImplemented(); }
float userIdleTime() { notImplemented(); return 0.0; }
bool DocumentLoader::getResponseModifiedHeader(WebCore::String&) const {notImplemented(); return false; }
void FrameView::updateBorder() { notImplemented(); }

}

bool AXObjectCache::gAccessibilityEnabled = false;

PassRefPtr<SharedBuffer> loadResourceIntoBuffer(const char*){ notImplemented();return RefPtr<SharedBuffer>(0);}

