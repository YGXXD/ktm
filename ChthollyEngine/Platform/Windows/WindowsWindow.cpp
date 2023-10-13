#include "WindowsWindow.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/AppEvent.h"
#include <windowsx.h>

keg::WindowsWindow::WindowsWindow(const WindowProps &props)
{
    InitProps(props);
}

keg::WindowsWindow::~WindowsWindow()
{
    EvtWin32Window::win32DelegateMap.erase(hWindow);
    DestroyWindow(hWindow);
}

LRESULT keg::WindowsWindow::WindowMsgCallBack(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_DESTROY:
    {
        keg::WindowCloseEvent e;
        eventCallback(e);
        return 0;
    }
    case WM_SIZE:
    {
        keg::WindowResizeEvent e(LOWORD(lParam), HIWORD(lParam));
	    eventCallback(e);
        return 0;
    }
    case WM_KEYDOWN:
    {
        keg::KeyPressedEvent e(wParam, (HIWORD(lParam) & 0x4000));
        eventCallback(e);
        return 0;
    }
    case WM_KEYUP:
    {
        keg::KeyReleasedEvent e(wParam);
        eventCallback(e);
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        keg::MouseButtonPressedEvent e(0);
        eventCallback(e);
        return 0;
    }
    case WM_MBUTTONDOWN:
    {
        keg::MouseButtonPressedEvent e(2);
        eventCallback(e);
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        keg::MouseButtonPressedEvent e(1);
        eventCallback(e);
        return 0;
    }
    case WM_LBUTTONUP:
    {
        keg::MouseButtonPressedEvent e(0);
        eventCallback(e);
        return 0;
    }
    case WM_MBUTTONUP:
    {
        keg::MouseButtonPressedEvent e(2);
        eventCallback(e);
        return 0;
    }
    case WM_RBUTTONUP:
    {
        keg::MouseButtonPressedEvent e(1);
        eventCallback(e);
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        keg::MouseMovedEvent e((float)(short)LOWORD(lParam), (float)(short)HIWORD(lParam));
        eventCallback(e);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void keg::WindowsWindow::InitProps(const WindowProps &props)
{
    title = props.title;
    RECT R = { 0, 0, static_cast<LONG>(props.width), static_cast<LONG>(props.height) };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;
    hWindow = CreateWindow(EvtWin32Window::windowClassName.c_str(), title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, GetModuleHandle(0), 0);

    EvtWin32Window::win32DelegateMap[hWindow] = this;
    ShowWindow(hWindow, SW_SHOW);
	UpdateWindow(hWindow);
}

void keg::WindowsWindow::OnUpdate()
{
}

uint32_t keg::WindowsWindow::GetWidth() const
{
    RECT R;
    GetWindowRect(hWindow, &R);
    return R.right - R.left;
}

uint32_t keg::WindowsWindow::GetHeight() const
{
    RECT R;
    GetWindowRect(hWindow, &R);
    return R.bottom - R.top;
}

void keg::WindowsWindow::SetVSync(bool enabled)
{
}

bool keg::WindowsWindow::IsVSync() const
{
    return false;
}

void *keg::WindowsWindow::GetNativeWindow() const
{
    return (void*)hWindow;
}
