#pragma once
#include <windows.h>


typedef struct Window Window;

Window* window_ctr(HWND hWnd, UINT w, UINT h, COLORREF bckgColor);


void window_setIsRendering(Window* wnd, BOOL w);
void window_updateClientRect(Window* wnd);

UINT window_getClientH(Window* wnd);
UINT window_getClientW(Window* wnd);
BOOL window_getIsRendering(Window* wnd);
HWND window_getHwnd(Window* wnd);
COLORREF window_getBckgColor(Window* wnd);
LPRECT window_getClientRect(Window* wnd);