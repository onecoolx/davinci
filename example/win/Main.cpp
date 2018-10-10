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

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
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
        }
        break;
    case WM_SIZE:
        {
        }
        break;
    case WM_LBUTTONDOWN:
        {
        }
        break;
    case WM_LBUTTONUP:
        {
        }
        break;
    case WM_RBUTTONDOWN:
        {
        }
        break;
    case WM_MOUSEMOVE:
        {
        }
        break;
    case WM_KEYDOWN:
        {
        }
        break;
    case WM_KEYUP:
        {
        }
        break;
    case WM_IME_CHAR:
        {
        }
        break;
	case WM_SETFOCUS:
		break;
	case WM_KILLFOCUS:
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

