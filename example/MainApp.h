/*
 * MainApp.h: Cross platform application framework.
 *
 * Copyright(C) 2018 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _MAIN_APPLICATION_H_
#define _MAIN_APPLICATION_H_

#include "davinci.h"

using namespace davinci;

class MainApp
{
public:
    MainApp();
    ~MainApp();
    
    void onInit(const WebSize& windowSize);
    void onDestroy(void);
    void onDraw(const WebRect& dirtyRect);
    void onResize(const WebSize& windowSize);

    void onMouseEvent(MouseEventType type, MouseButtonType button, const WebPoint& point, unsigned int modifier);
    void onKeyboardEvent(KeyEventType type, VirtualKeyType key, unsigned int modifier);
    void onInputEvent(const WebString& str);
    void onFocusEvent(bool focus);
    void onContextMenuEvent(const WebPoint& point, unsigned int modifier);

    void loadUrl(const WebUrl& url);
public:
    int dispatchEvents(void);
private:
};
#endif /*_MAIN_APPLICATION_H_*/
