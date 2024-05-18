#include "window.h"

struct Window {
    HWND hWnd;
    UINT width;
    UINT height;
    BOOL isRendering;
    COLORREF bckgColor;
    LPRECT clientRect;
};

Window* window_ctr(HWND hWnd, UINT w, UINT h, COLORREF bckgColor) {
    Window* wnd = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*wnd));
    wnd->hWnd = hWnd;
    wnd->width = w;
    wnd->height = h;
    wnd->bckgColor = bckgColor;
    wnd->clientRect = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(RECT));
    window_updateClientRect(wnd);
    return wnd;
}

void window_updateClientRect(Window* wnd) {
    GetClientRect(wnd->hWnd, wnd->clientRect);
}
// Seters
void window_setIsRendering(Window* wnd, BOOL w) {
    wnd->isRendering = w;
}


// Geters
BOOL window_getIsRendering(Window* wnd) {
    return wnd->isRendering;
}

UINT window_getClientW(Window* wnd) {
    return wnd->clientRect->right;
}

UINT window_getClientH(Window* wnd) {
    return wnd->clientRect->bottom;
}

LPRECT window_getClientRect(Window* wnd) {
    return wnd->clientRect;
}


HWND window_getHwnd(Window* wnd) {
    return wnd->hWnd;
}

COLORREF window_getBckgColor(Window* wnd) {
    return wnd->bckgColor;
}