#include <windows.h>
#include "window.h"

void renderer();
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Window* wnd;

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
    WNDCLASS wc = { 0 }; 
    wc.lpszClassName = L"mywnd";
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WndProc;
    RegisterClass(&wc);
    HWND hWnd = CreateWindowEx(0, L"mywnd", L"My window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, 0, 0);
    MSG msg;
    while(GetMessage(&msg, hWnd, 0 , 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch(uMsg) {
        case WM_CREATE:
            wnd = window_ctr(hWnd, 800, 600, RGB(0, 255, 255));
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)renderer, 0, 0, 0);
            window_setIsRendering(wnd, TRUE);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            ExitProcess(0);
            break;
        case WM_ERASEBKGND:
            return TRUE;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
            break;
    }
}

void renderer() {
    HWND hWnd = window_getHwnd(wnd);
    HDC hdc = GetDC(hWnd);
    HDC backDC = CreateCompatibleDC(hdc);
    //ReleaseDC(hWnd, hdc);
    SelectObject(backDC, CreateSolidBrush(window_getBckgColor(wnd)));


    while(window_getIsRendering(wnd)) {
        window_updateClientRect(wnd);
        LPRECT clientRect = window_getClientRect(wnd);
        HBITMAP backBmp = CreateCompatibleBitmap(hdc, clientRect->right, clientRect->bottom);
        DeleteObject(SelectObject(backDC, backBmp));
        Rectangle(backDC, 0, 0, window_getClientW(wnd), window_getClientH(wnd));
        Ellipse(backDC, 0, 0, 100, 100);
        BitBlt(hdc, 0, 0, clientRect->right, clientRect->bottom, backDC, 0, 0, SRCCOPY);
        InvalidateRect(hWnd, 0, 0);
        Sleep(16);
        DeleteObject(backBmp);
    }

    ReleaseDC(hWnd, hdc);
    DeleteDC(backDC);
}