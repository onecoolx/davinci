/*
 * MainApp.h: Cross platform application framework.
 *
 * Copyright(C) 2018 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "MainApp.h"

using namespace davinci;

MainApp::MainApp()
    : m_view(NULL)
    , m_client(NULL)
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
}

MainApp::~MainApp()
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
}

void MainApp::onInit(const WebSize& windowSize)
{
    m_client = new ViewClient();
    m_view = new WebView(*m_client, windowSize);

    fprintf(stderr, "%s : %s : %d  size:[%d, %d]\n", __FILE__, __FUNCTION__, __LINE__, windowSize.width(), windowSize.height());
}

void MainApp::onDestroy(void)
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
    if (m_view) {
        delete m_view;
        m_view = NULL;
    }
    if (m_client) {
        delete m_client;
        m_client = NULL;
    }
}

void MainApp::onDraw(const WebRect& dirtyRect)
{
    fprintf(stderr, "%s : %s : %d drawRect[%d, %d, %d, %d]\n", __FILE__, __FUNCTION__, __LINE__, dirtyRect.x(), dirtyRect.y(), dirtyRect.width(), dirtyRect.height());
}

void MainApp::onResize(const WebSize& windowSize)
{
    fprintf(stderr, "%s : %s : %d resize:[%d %d]\n", __FILE__, __FUNCTION__, __LINE__, windowSize.width(), windowSize.height());
}

void MainApp::onMouseEvent(MouseEventType type, MouseButtonType button, const WebPoint& point, unsigned int modifier)
{
    fprintf(stderr, "%s : %s : %d type: %d  btn: %d  point: [%d - %d] modifier: %d\n", __FILE__, __FUNCTION__, __LINE__, type, button, point.x(), point.y(), modifier);
}

void MainApp::onKeyboardEvent(KeyEventType type, VirtualKeyType key, unsigned int modifier)
{
    fprintf(stderr, "%s : %s : %d type: %d key: %d modifier: %d\n", __FILE__, __FUNCTION__, __LINE__, type, key, modifier);
}

void MainApp::onInputEvent(const WebString& str)
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
}

void MainApp::onFocusEvent(bool focus)
{
    fprintf(stderr, "%s : %s : %d  focus : %d \n", __FILE__, __FUNCTION__, __LINE__, focus ? 1 : 0);
}

void MainApp::onContextMenuEvent(const WebPoint& point, unsigned int modifier)
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
}

void MainApp::loadUrl(const WebUrl& url)
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
}

// event loop callback
int MainApp::dispatchEvents(void)
{
    fprintf(stderr, "%s : %s : %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}
