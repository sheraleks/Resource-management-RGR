//#pragma comment( lib, "user32.lib" )
#include <windows.h>
#include <shlwapi.h> 
#pragma comment(lib, "shlwapi.lib") // for wnsprintf


// тут косяки
/*

int a = -1; // volatile identifier is for thread-safety
volatile int l = -1; // this is not volatile due to passing by reference
volatile library_info li; // volatile identifier is for thread-safety


DWORD WINAPI ThreadFunc(void* lParam) {
    library_info* ret = (library_info*)lParam;
    GetMetricLevel2(ret);
    return 0;
}
*/
#define BUFSIZE 64
TCHAR buf[BUFSIZE];

struct info
{
    int fn_keys;
};

info info1;

DWORD WINAPI ThreadFunc(void* st)
{
    info* ret = (info *)st;
    ret->fn_keys = GetKeyboardType(2);
	//num = (void*);
	return 0;
}

LRESULT __stdcall WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS windowClass = { 0 };
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = L"RES_MAN";
    RegisterClass(&windowClass);

    HWND hwnd = CreateWindow(
        windowClass.lpszClassName,
        L"Resource management",
        WS_OVERLAPPEDWINDOW,
        100, 50, 500, 150,
        nullptr, nullptr,
        hInstance,
        nullptr);
    // запуск процесса
    HANDLE hThread;
    DWORD IDThread;
    hThread = CreateThread(NULL, 0, ThreadFunc, &info1, 0, &IDThread);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    //
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}

LRESULT __stdcall WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC dc;

    switch (message)
    {
    case WM_PAINT:
        dc = BeginPaint(hWnd, &ps);
        wsprintf(buf, L"Count of FN-keys on current keyboard: %d", info1.fn_keys);
        TextOut(dc, 30, 20, buf, lstrlen(buf));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}