/*
** webview.h: webview implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#ifndef _WEBVIEW_H_
#define _WEBVIEW_H_

#include "macross.h"

#include <wtf/Noncopyable.h>
#include <wtf/OwnPtr.h>
#include "WidgetView.h"
#include "PlatformMouseEvent.h"
#include "PlatformWheelEvent.h"
#include "PlatformKeyboardEvent.h"

namespace WebCore {
    class Frame;
	class ScrollView;
    class EditorClientMC;
    class ChromeClientMC;
    class FrameLoaderClientMC;
}

namespace MaCross {

class WebViewPrivate;

class WebView : public WebCore::WidgetView
{
public:
	WebView(struct _mc_view* view, unsigned char* buffer, int width, int height, int pitch);
	~WebView();

	void resizeView(unsigned char* buffer, int width, int height, int pitch);
	void updateRect(int x, int y, int width, int height);
	void scrollRect(int sx, int sy, int x, int y, int width, int height);
	void paintView(void);
	void updateViewNow(void);

	void contentsPosChanged(int old_x, int old_y, int new_x, int new_y);

	void setDirtyRect(int x, int y, int width, int heignt);

	void setMinLayoutSize(int w, int h);
	void clearMinLayoutSize(void);

	_mc_size getSize(void) const;
public:
    //navigation
	void loadUrl(const char* url, bool lock);
	void loadHtml(const char* str, const char* rurl);
    void forward(void);
    void backward(void);
    void stop(void);
	void reload(void);
	void reflow(void);
	void repaint(void);

public:
	//event hander
	bool mouseUp(_mc_mouse_btn button, unsigned modifier, int x, int y);
	bool mouseDown(_mc_mouse_btn button, unsigned modifier, int x, int y);
	bool mouseMove(_mc_mouse_btn button, unsigned modifier, int x, int y);
	bool mouseWheel(_mc_mouse_btn button, unsigned modifier, int x, int y);

	bool keyUp(_mc_key_sym key, unsigned modifier);
	bool keyDown(_mc_key_sym key, unsigned modifier);

	bool contextMenu(unsigned modifier, int x, int y);

	bool textInput(const char* text);
	//focus
    void setFocus(void);
    void killFocus(void);
	//encoding
	void setEncodingName(_mc_encoding name);
	_mc_encoding encodingName(void);
	//source
	void setViewSource(bool b);
	//render mode
	int renderMode(void);
	void setRenderMode(int mode, int limit);	
	//position
	void setContentsPosition(int x, int y);
	void contentsPosition(int *x, int *y);
	_mc_size contentsSize(void);
	//search text
    bool search(const char *str, bool forward, bool caseSensitive, bool wrap);
    int markAll(const char *str, bool caseSensitive, bool highlight, unsigned int limit);
    void unmarkAll(void);
	//text scale
	int textScale(void);
	void setTextScale(int factor);
	//page scale
	int scaleFactor(void);
	void setScaleFactor(int scale);
	//javascript
	void executeScript(const char* script);
	//font antialias
	bool isTextAntialias(void); 
	void setTextAntialias(bool b);
private:
    friend class WebCore::EditorClientMC;
    friend class WebCore::ChromeClientMC;
    friend class WebCore::FrameLoaderClientMC;
	friend class WebCore::ScrollView;
	void firstLayout(void);
	void resizeContents(int,int);
    //attributes
    WebCore::Frame * mainframe(void);
    OwnPtr<WebViewPrivate> d;
};

WebCore::MouseButton _get_mouse_button(_mc_mouse_btn button);
}

#endif/*_WEBVIEW_H_*/
