/* functions.cpp - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#include <windows.h>
#include "macross.h"

extern MaCrossView* OpenWindow(const char*, int,int);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void update_rect(void *p, int x, int y, int w, int h)
{
	HWND hw = (HWND)p;

	RECT rc = {x, y, x+w, y+h};
	InvalidateRect(hw, &rc, TRUE);
}

void update_window(void *p)
{
	HWND hw = (HWND)p;
	UpdateWindow(hw);
}

void set_title(void *p, const char* text)
{
}

void change_cursor(int c)
{
	switch (c) {
	case 1:
    	SetCursor(LoadCursor(0, IDC_CROSS));
		break;
	case 2:
    	SetCursor(LoadCursor(0, IDC_HAND));
		break;
	case 3:
    	SetCursor(LoadCursor(0, IDC_SIZE));
		break;
	case 4:
    	SetCursor(LoadCursor(0, IDC_IBEAM));
		break;
	case 5:
    	SetCursor(LoadCursor(0, IDC_WAIT));
		break;
	case 6:
    	SetCursor(LoadCursor(0, IDC_HELP));
		break;
	default:
    	SetCursor(LoadCursor(0, IDC_ARROW));
		break;
	}
}

MaCrossView* window_open(const char* url, int x, int y, int w, int h)
{
//	return OpenWindow(url, w, h);
	return 0;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */