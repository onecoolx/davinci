/* main.cpp - MaCross application 
 * 
 * Copyright (C) 2011 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#include <stdio.h>
#include <windows.h>

#include "macross.h"
#include "interface.h"


HWND hmWnd;
HINSTANCE hInst;	
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

static int CBYTE = 0;
static int CBIT = 0;
static int width = 800;
static int height = 600;
static const char* home_url = 0;

static BITMAP bmp;
static BYTE* buffer = 0;
static MaCrossView * view = 0;

extern void init_callback(void);

HWND getMainWindow()
{
	return hmWnd;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message) {
	case WM_CREATE:
		{
			hdc = GetDC(hWnd);
			CBIT = GetDeviceCaps(hdc, BITSPIXEL);	
			CBYTE = CBIT/8;
			ReleaseDC(hWnd, hdc);
			
			buffer = (BYTE*)malloc(width * height * CBYTE);
			memset(buffer, 0xFF, width * height * CBYTE);
			bmp.bmType = 0;
			bmp.bmWidth = width;
			bmp.bmHeight = height;
			bmp.bmWidthBytes = width * CBYTE;
			bmp.bmPlanes = 1;
			bmp.bmBitsPixel = CBIT;
			bmp.bmBits = (LPVOID)buffer;

			view = on_init(buffer, width, height, width * CBYTE, hWnd);	

			load_url(view, home_url);
			
			SetTimer(hWnd, 33, 10, 0);

		}
		break;
	case WM_PAINT:
		{
			HDC mdc;
			HGDIOBJ h;
			RECT crc;
			HBITMAP hbmp;
#if _WIN32_WCE
			BITMAP* pm;
#endif
			GetUpdateRect(hWnd, &crc, FALSE);

			hdc = BeginPaint(hWnd, &ps);
			on_draw(view, crc.left, crc.top, crc.right-crc.left, crc.bottom-crc.top);
			mdc = CreateCompatibleDC(hdc);
#if _WIN32_WCE
			pm = &bmp;
			hbmp = CreateBitmap(pm->bmWidth, pm->bmHeight, pm->bmPlanes, pm->bmBitsPixel, pm->bmBits);
#else
			hbmp = CreateBitmapIndirect(&bmp);
#endif
			h = SelectObject(mdc, hbmp);
			BitBlt(hdc, crc.left, crc.top, crc.right-crc.left, crc.bottom-crc.top, 
														mdc, crc.left, crc.top, SRCCOPY);
			SelectObject(mdc, h);
			DeleteObject(hbmp);
			DeleteDC(mdc);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_SIZE:
		{
			if (view) {
				width = LOWORD(lParam);
				height = HIWORD(lParam);
				free(buffer);

				if (width < 1) width = 1;
				if (height < 1) height = 1;

				buffer = (BYTE*)malloc(width * height * CBYTE);
				memset(buffer, 0xFF, width * height * CBYTE);
				bmp.bmType = 0;
				bmp.bmWidth = width;
				bmp.bmHeight = height;
				bmp.bmWidthBytes = width*CBYTE;
				bmp.bmPlanes = 1;
				bmp.bmBitsPixel = CBIT;
				bmp.bmBits = buffer;

				on_size(view, buffer, width, height, width * CBYTE);
			}
		}
		break;
	case WM_TIMER:
		macross_event_dispatch();
		break;
	case WM_LBUTTONDOWN:
		{
			unsigned key = 0;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			on_mouse(view, EVT_MOUSE_DOWN, MOUSE_BTN_LEFT, x, y, key);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			unsigned key = 0;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			on_context_menu(view, x, y, key);
		}
		break;
	case WM_KEYDOWN:
		{
			on_key(view, EVT_KEY_DOWN, (MC_VIRTUAL_KEY)wParam, 0);
		}
		break;
	case WM_IME_CHAR:
		{
			wchar_t uc = 0;
			unsigned char mc[3] = {0};
			mc[0] = (wParam >> 8) & 0xFF;
			mc[1] = wParam & 0xFF;
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char*)&mc, -1, &uc, 1);
			wParam = uc;
		}
	case WM_CHAR:
		{
			on_chars(view, (char*)(&wParam));
		}
		break;
	case WM_KEYUP:
		{
			on_key(view, EVT_KEY_UP, (MC_VIRTUAL_KEY)wParam, 0);
		}
		break;
	case WM_LBUTTONUP:
		{
			unsigned key = 0;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			on_mouse(view, EVT_MOUSE_UP, MOUSE_BTN_LEFT, x, y, key);
		}
		break;
	case WM_MOUSEMOVE:
		{
			unsigned key = 0;
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (wParam == MK_CONTROL)
				key |= MF_CTRL;
			if (wParam == MK_SHIFT)
				key |= MF_SHIFT;

			on_mouse(view, EVT_MOUSE_MOVE, (MC_MOUSE_BUTTON)0, x, y, key);
		}
		break;
	case WM_SETFOCUS:
		on_focus(view);
		break;
	case WM_KILLFOCUS:
		on_lose_focus(view);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_DESTROY:
		{
			KillTimer(hWnd, 33);
			on_term(view);
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	hmWnd = CreateWindow(L"MaCross", L"MaCross Browser", WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (!hmWnd) {
		return FALSE;
	}
	
	ShowWindow(hmWnd, nCmdShow);
	UpdateWindow(hmWnd);
	
	return TRUE;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC)WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= 0;
	wc.hCursor			= 0;
	wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= L"MaCross";
	
	return RegisterClass(&wc);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (lpCmdLine)
    	home_url = lpCmdLine;


	macross_initialize(PIXEL_FORMAT_BGRA32, 1024, 768);

	init_callback();

	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	macross_shutdown();
	return msg.wParam;
}

