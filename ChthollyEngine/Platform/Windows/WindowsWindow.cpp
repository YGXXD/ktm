#include "WindowsWindow.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/AppEvent.h"
#include <windowsx.h>

std::string ktl::WindowsWindow::windowClassName = "ChthollyWindow";

void ktl::WindowsWindow::WindowsWin32Init()
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = EvtWin32Window::WindowMsgProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(0);
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = windowClassName.c_str();
    RegisterClass(&wc);
}

void ktl::WindowsWindow::WindowsWin32PollEvent()
{
    MSG msg = { };
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void ktl::WindowsWindow::WindowsWin32Quit()
{
    UnregisterClass(windowClassName.c_str(), GetModuleHandle(0));
}

ktl::WindowsWindow::WindowsWindow(const WindowProps &props)
{
    InitProps(props);
}

ktl::WindowsWindow::~WindowsWindow()
{
    EvtWin32Window::win32DelegateMap.erase(hWindow);
    DestroyWindow(hWindow);
}

LRESULT ktl::WindowsWindow::WindowMsgCallBack(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_DESTROY:
    {
        ktl::WindowCloseEvent e;
        eventCallback(e);
        return 0;
    }
    case WM_SIZE:
    {
        ktl::WindowResizeEvent e(LOWORD(lParam), HIWORD(lParam));
	    eventCallback(e);
        return 0;
    }
    case WM_KEYDOWN:
    {
        ktl::KeyPressedEvent e(wParam, (HIWORD(lParam) & 0x4000));
        eventCallback(e);
        return 0;
    }
    case WM_KEYUP:
    {
        ktl::KeyReleasedEvent e(wParam);
        eventCallback(e);
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        ktl::MouseButtonPressedEvent e(0);
        eventCallback(e);
        return 0;
    }
    case WM_MBUTTONDOWN:
    {
        ktl::MouseButtonPressedEvent e(2);
        eventCallback(e);
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        ktl::MouseButtonPressedEvent e(1);
        eventCallback(e);
        return 0;
    }
    case WM_LBUTTONUP:
    {
        ktl::MouseButtonPressedEvent e(0);
        eventCallback(e);
        return 0;
    }
    case WM_MBUTTONUP:
    {
        ktl::MouseButtonPressedEvent e(2);
        eventCallback(e);
        return 0;
    }
    case WM_RBUTTONUP:
    {
        ktl::MouseButtonPressedEvent e(1);
        eventCallback(e);
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        ktl::MouseMovedEvent e((float)(short)LOWORD(lParam), (float)(short)HIWORD(lParam));
        eventCallback(e);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void ktl::WindowsWindow::InitProps(const WindowProps &props)
{
    title = props.title;
    RECT R = { 0, 0, static_cast<LONG>(props.width), static_cast<LONG>(props.height) };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;
    hWindow = CreateWindow(windowClassName.c_str(), title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, GetModuleHandle(0), 0);

    EvtWin32Window::win32DelegateMap[hWindow] = this;
    ShowWindow(hWindow, SW_SHOW);
	UpdateWindow(hWindow);
}

void ktl::WindowsWindow::OnUpdate()
{
}

uint32_t ktl::WindowsWindow::GetWidth() const
{
    RECT R;
    GetWindowRect(hWindow, &R);
    return R.right - R.left;
}

uint32_t ktl::WindowsWindow::GetHeight() const
{
    RECT R;
    GetWindowRect(hWindow, &R);
    return R.bottom - R.top;
}

void ktl::WindowsWindow::SetVSync(bool enabled)
{
}

bool ktl::WindowsWindow::IsVSync() const
{
    return false;
}

void *ktl::WindowsWindow::GetNativeWindow() const
{
    return (void*)hWindow;
}
