/* popmenu - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#include <stdlib.h>
#include <windows.h>
#include "macross.h"

extern HWND getMainWindow();

struct menu_data {
	MC_POPUP_MENU * menu;
	BITMAP bmp;
};

LRESULT CALLBACK POPWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC hdc;
	struct menu_data* menu;
	
	switch (message) 
	{
	case WM_CREATE:
		{
			int CBIT, CBYTE;
			int width, height;
			unsigned char * buffer;
			LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
			hdc = GetDC(hWnd);
			CBIT = GetDeviceCaps(hdc, BITSPIXEL);	
			CBYTE = CBIT/8;
			ReleaseDC(hWnd, hdc);

			menu = (struct menu_data*)malloc(sizeof(struct menu_data));
			menu->menu = (MC_POPUP_MENU *)cs->lpCreateParams;
			width = cs->cx;
			height = cs->cy;

			buffer = (BYTE*)malloc(width*height*CBYTE);
			memset(buffer, 0xFF, width*height*CBYTE);
			menu->bmp.bmType = 0;
			menu->bmp.bmWidth = width;
			menu->bmp.bmHeight = height;
			menu->bmp.bmWidthBytes = width*CBYTE;
			menu->bmp.bmPlanes = 1;
			menu->bmp.bmBitsPixel = CBIT;
			menu->bmp.bmBits = buffer;
			menu->menu->buffer = buffer;
			menu->menu->pitch = width*CBYTE;

			SetWindowLong(hWnd, GWL_USERDATA, (LONG)menu);
		}
		break;
	case WM_PAINT:
		{
			HDC mdc;
			HBITMAP hbmp;
			HGDIOBJ h;
			RECT crc;
			MC_RECT rc;
#if _WIN32_WCE
			BITMAP* pm;
#endif
			GetClientRect(hWnd, &crc);
			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);
			rc.x = crc.left;  rc.y = crc.top; rc.w = crc.right-crc.left; rc.h = crc.bottom-crc.top;
			macross_menu_update(menu->menu, &rc);
			hdc = BeginPaint(hWnd, &ps);
			mdc = CreateCompatibleDC(hdc);
#if _WIN32_WCE
			pm = &menu->bmp;
			hbmp = CreateBitmap(pm->bmWidth, pm->bmHeight, pm->bmPlanes, pm->bmBitsPixel, pm->bmBits);
#else
			hbmp = CreateBitmapIndirect(&menu->bmp);
#endif
			h = SelectObject(mdc, hbmp);
			BitBlt(hdc, 0, 0, crc.right-crc.left, crc.bottom-crc.top, mdc, 0, 0, SRCCOPY);
			SelectObject(mdc, h);
			DeleteObject(hbmp);
			DeleteDC(mdc);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_SIZE:
		{
			int CBIT, CBYTE;
			int width, height;
			unsigned char * buffer;

			hdc = GetDC(hWnd);
			CBIT = GetDeviceCaps(hdc, BITSPIXEL);	
			CBYTE = CBIT/8;
			ReleaseDC(hWnd, hdc);

			width = LOWORD(lParam);
			height = HIWORD(lParam);

			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);
 
			if (menu) {
				free(menu->menu->buffer);

				if (width < 1) width = 1;
				if (height < 1) height = 1;

				buffer = (BYTE*)malloc(width*height*CBYTE);
				memset(buffer, 0xFF, width*height*CBYTE);
				menu->bmp.bmType = 0;
				menu->bmp.bmWidth = width;
				menu->bmp.bmHeight = height;
				menu->bmp.bmWidthBytes = width*CBYTE;
				menu->bmp.bmPlanes = 1;
				menu->bmp.bmBitsPixel = CBIT;
				menu->bmp.bmBits = buffer;
				menu->menu->pitch = width*CBYTE;
				menu->menu->buffer = buffer;
				macross_menu_resize(menu->menu, width, height);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			unsigned key = 0;
			MC_MOUSE_EVENT e;
			MC_POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);

			e.type = EVT_MOUSE_DOWN;
			e.button =  MOUSE_BTN_LEFT;
			e.point = pt;
			e.modifier = key;
			macross_menu_mouse_event(menu->menu, &e);
		}
		break;
	case WM_KEYDOWN:
		{
			unsigned key = 0;
			MC_KEY_EVENT e;
			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);

			e.type = EVT_KEY_DOWN;
			e.key = (MC_VIRTUAL_KEY)wParam;
			e.modifier = key;
			macross_menu_keyboard_event(menu->menu, &e);
		}
		break;
	case WM_LBUTTONUP:
		{
			unsigned key = 0;
			MC_MOUSE_EVENT e;
			MC_POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);

			e.type = EVT_MOUSE_UP;
			e.button =  MOUSE_BTN_LEFT;
			e.point = pt;
			e.modifier = key;
			macross_menu_mouse_event(menu->menu, &e);
		}
		break;
	case WM_MOUSEMOVE:
		{
			unsigned key = 0;
			MC_MOUSE_EVENT e;
			MC_POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);

			e.type = EVT_MOUSE_MOVE;
			e.button =  MOUSE_BTN_NONE;
			e.point = pt;
			e.modifier = key;
			macross_menu_mouse_event(menu->menu, &e);
		}
		break;
	case WM_KILLFOCUS:
		{
			ReleaseCapture();
			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);
			macross_menu_hide(menu->menu);
		}
		break;
	case WM_ERASEBKGND:
		break;
	case WM_DESTROY:
		{
			menu = (struct menu_data*)GetWindowLong(hWnd, GWL_USERDATA);
			free(menu->menu->buffer);
			free(menu);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM PopRegisterClass()
{
	WNDCLASS wc;
	
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= (WNDPROC)POPWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= 0;
	wc.hIcon			= 0;
	wc.hCursor		= 0;
	wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName	= 0;
	wc.lpszClassName	= L"POPMenu";
	
	return RegisterClass(&wc);
}


static void initPopMenu()
{
	static int init = 0;
	if (!init) {
		PopRegisterClass();
		init = 1;
	}
}

static void Hide(MC_POPUP_MENU* m)
{
	HWND p = (HWND)m->data;
	ShowWindow(p, SW_HIDE);
}

static void Show(MC_POPUP_MENU* m)
{
	HWND p = (HWND)m->data;
	ShowWindow(p, SW_SHOW);
}

static void Move(MC_POPUP_MENU* m, const MC_RECT* r)
{
	POINT pt = {r->x, r->y};
	HWND p = (HWND)m->data;
	ClientToScreen(getMainWindow(), &pt);
	MoveWindow(p, pt.x, pt.y, r->w, r->h, FALSE);
	m->rect = *r;
}

static void Update(MC_POPUP_MENU* m)
{
	HWND p = (HWND)m->data;
	UpdateWindow(p);
}

static void Dirty(MC_POPUP_MENU* m, const MC_RECT* r)
{
	HWND p = (HWND)m->data;
	if (r) {
		RECT rc = {r->x, r->y, r->x+r->w+1, r->y+r->h+1};
		InvalidateRect(p, &rc, FALSE);
	} else
		InvalidateRect(p, 0, FALSE);
}

static void Capture(MC_POPUP_MENU* m)
{
	HWND p = (HWND)m->data;
	SetFocus(p);
	SetCapture(p);
}

MC_POPUP_MENU* create_popmenu(const MC_RECT* r)
{
	POINT pt = {r->x, r->y};
	MC_POPUP_MENU * p = (MC_POPUP_MENU*)malloc(sizeof(MC_POPUP_MENU));
	memset(p, 0, sizeof(MC_POPUP_MENU));

	initPopMenu();

	p->rect = *r;
	ClientToScreen(getMainWindow(), &pt);
	p->data = (void*)CreateWindow(L"POPMenu", L"popmenu", WS_POPUP|WS_VISIBLE, pt.x, pt.y, r->w, r->h, getMainWindow(), 0, 0, p);

	p->show = Show;
	p->hide = Hide;
	p->move = Move;
	p->dirty = Dirty;
	p->update = Update;
	p->capture = Capture;

	return p;
}

void destroy_popmenu(MC_POPUP_MENU* m)
{
	HWND p = (HWND)m->data;
	DestroyWindow(p);
	free(m);
}
