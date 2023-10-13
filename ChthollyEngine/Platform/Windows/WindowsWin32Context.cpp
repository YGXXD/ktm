#include "WindowsWin32Context.h"

std::string keg::WindowsWindow::windowClassName = "ChthollyWindow";

void keg::WindowsWindow::WindowsWin32Init()
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

void keg::WindowsWindow::WindowsWin32PollEvent()
{
    MSG msg = { };
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void keg::WindowsWindow::WindowsWin32Quit()
{
    UnregisterClass(windowClassName.c_str(), GetModuleHandle(0));
}
