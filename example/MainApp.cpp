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

MainApp::MainApp(ViewClient& client, const WebSize& size)
    : m_view(new WebView(client, size))
{
}

MainApp::~MainApp()
{
    delete m_view;
}

void MainApp::onInit(const WebSize& windowSize)
{
}

void MainApp::onDestroy(void)
{
}

void MainApp::onDraw(const WebRect& dirtyRect)
{
}

void MainApp::onResize(const WebSize& windowSize)
{
}

void MainApp::onMouseEvent(MouseEventType type, MouseButtonType button, const WebPoint& point, unsigned int modifier)
{
}

void MainApp::onKeyboardEvent(KeyEventType type, VirtualKeyType key, unsigned int modifier)
{
}

void MainApp::onInputEvent(const WebString& str)
{
}

void MainApp::onFocusEvent(bool focus)
{
}

void MainApp::onContextMenuEvent(const WebPoint& point, unsigned int modifier)
{
}

void MainApp::loadUrl(const WebUrl& url)
{
}

