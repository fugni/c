#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdbool.h>

bool quit = false;

LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    WNDCLASS window_class = { 0 };
    const wchar_t window_class_name[] = L"My Window Class";
    window_class.hbrBackground = CreateSolidBrush(0xff66cc);
    window_class.lpszClassName = window_class_name;
    window_class.lpfnWndProc = WindowProcessMessage;
    window_class.hInstance = hInstance;
    
    RegisterClass(&window_class);
    
    HWND window_handle = CreateWindow(window_class_name, L"haiiii :3", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);
    if(window_handle == NULL) { return -1; }
    
    ShowWindow(window_handle, nCmdShow);
    
    while(!quit) {
        MSG message;
        while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        
        HFONT font = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
        HDC device_context = GetDC(window_handle);
        SelectObject(device_context, font);
        TextOut(device_context, 100, 200, L"pinaple on pizza is an abomination", 34);
        TextOut(device_context, 120, 230, L"-ghandi", 7);
        ReleaseDC(window_handle, device_context);

    }
    
    return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_QUIT:
        case WM_DESTROY: {
            quit = true;
        } break;
        
        default: { // Message not handled; pass on to default message handling function
            return DefWindowProc(window_handle, message, wParam, lParam);
        } break;
    }
    return 0;
}