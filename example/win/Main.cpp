/*
 * MainApp.h: Cross platform application framework.
 *
 * Copyright(C) 2018 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include "../MainApp.h"

// console debug
// #pragma comment( linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")

static int width = 0;
static int height = 0;

MainApp* mainApp = NULL;

HINSTANCE hInst;    
HWND hmWnd;
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void CALLBACK Func(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    if (mainApp) {
        mainApp->dispatchEvents();
    }
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    MSG msg;
    MyRegisterClass(hInstance);

    width = 800;
    height = 600;

    if (!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }

    SetTimer(NULL, 999, 10, (TIMERPROC)Func);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    KillTimer(NULL, 999);
    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    
    wcex.cbSize = sizeof(WNDCLASSEX); 
    
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = (WNDPROC)WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = 0;
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = L"Demo";
    wcex.hIconSm        = 0;
    
    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    hmWnd = CreateWindow(L"Demo", L"davinci demo", WS_OVERLAPPEDWINDOW,
        0, 0, width, height, NULL, NULL, hInstance, NULL);
    if (!hmWnd) {
        return FALSE;
    }
    
    ShowWindow(hmWnd, nCmdShow);
    UpdateWindow(hmWnd);
    
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{    
    PAINTSTRUCT ps;
    HDC hdc;
    
    switch (message) {
    case WM_CREATE:
        {
            mainApp = new MainApp();
            mainApp->onInit(WebSize(width, height));
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            mainApp->onDraw(WebRect(ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top));
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        {
            int new_width = LOWORD(lParam);
            int new_height = HIWORD(lParam);

            if (new_width != width || new_height != height) {

                width = new_width;
                height = new_height;

                if (width < 1) {
                    width = 1;
                }
                if (height < 1) {
                    height = 1;
                }

                mainApp->onResize(WebSize(width, height));
            }
        }
        break;
    case WM_LBUTTONDOWN:
        {
            unsigned int modifiers = 0;
            if (wParam & MK_SHIFT)
                modifiers |= DF_SHIFT;
            if (wParam & MK_CONTROL)
                modifiers |= DF_CTRL;

            mainApp->onMouseEvent(EVT_MOUSE_DOWN, MOUSE_BTN_LEFT, WebPoint(LOWORD(lParam), HIWORD(lParam)), modifiers);
        }
        break;
    case WM_LBUTTONUP:
        {
            unsigned int modifiers = 0;
            if (wParam & MK_SHIFT)
                modifiers |= DF_SHIFT;
            if (wParam & MK_CONTROL)
                modifiers |= DF_CTRL;

            mainApp->onMouseEvent(EVT_MOUSE_UP, MOUSE_BTN_LEFT, WebPoint(LOWORD(lParam), HIWORD(lParam)), modifiers);
        }
        break;
    case WM_RBUTTONDOWN:
        {
            unsigned int modifiers = 0;
            if (wParam & MK_SHIFT)
                modifiers |= DF_SHIFT;
            if (wParam & MK_CONTROL)
                modifiers |= DF_CTRL;

            mainApp->onContextMenuEvent(WebPoint(LOWORD(lParam), HIWORD(lParam)), modifiers);
        }
        break;
    case WM_MOUSEMOVE:
        {
            unsigned int modifiers = 0;
            MouseButtonType key = MOUSE_BTN_NONE;
            if (wParam & MK_LBUTTON)
                key = MOUSE_BTN_LEFT;
            else if (wParam & MK_RBUTTON)
                key = MOUSE_BTN_RIGHT;

            if (wParam & MK_SHIFT)
                modifiers |= DF_SHIFT;
            if (wParam & MK_CONTROL)
                modifiers |= DF_CTRL;

            mainApp->onMouseEvent(EVT_MOUSE_MOVE, key, WebPoint(LOWORD(lParam), HIWORD(lParam)), modifiers);
        }
        break;
    case WM_KEYDOWN:
        mainApp->onKeyboardEvent(EVT_KEY_DOWN, (VirtualKeyType)wParam, 0);
        break;
    case WM_KEYUP:
        mainApp->onKeyboardEvent(EVT_KEY_UP, (VirtualKeyType)wParam, 0);
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
        mainApp->onInputEvent(WebString((char*)(&wParam)));
        break;
    case WM_SETFOCUS:
        mainApp->onFocusEvent(true);
        break;
    case WM_KILLFOCUS:
        mainApp->onFocusEvent(false);
        break;
    case WM_ERASEBKGND:
        break;    
    case WM_DESTROY:
        {
            mainApp->onDestroy();
            delete mainApp;
            PostQuitMessage(0);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

