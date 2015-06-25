/* functions.cpp - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#include "macross.h"
#include <QMainWindow>
#include <QDebug>

extern QMainWindow* getMainWindow();
extern MaCrossView* OpenWindow(const char*, int,int);
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void update_rect(void *p, int x, int y, int w, int h)
{
	QMainWindow* main = (QMainWindow*)p;
	main->update(x, y, w, h);
}

void set_title(void *p, const char* text)
{
	QMainWindow* main = (QMainWindow*)p;
	QString s = QString::fromUtf8(text);
	main->setWindowTitle(s);
}

void update_window(void *p)
{
}

void change_cursor(int c)
{
	QMainWindow* window = getMainWindow();
	switch (c) {
	case 1:
    	window->setCursor(Qt::CrossCursor);
		break;
	case 2:
    	window->setCursor(Qt::PointingHandCursor);
		break;
	case 3:
    	window->setCursor(Qt::SizeAllCursor);
		break;
	case 4:
    	window->setCursor(Qt::IBeamCursor);
		break;
	case 5:
    	window->setCursor(Qt::WaitCursor);
		break;
	case 6:
    	window->setCursor(Qt::WhatsThisCursor);
		break;
	default:
    	window->setCursor(Qt::ArrowCursor);
		break;
	}
}

MaCrossView* window_open(const char* url, int x, int y, int w, int h)
{
	return OpenWindow(url, w, h);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
