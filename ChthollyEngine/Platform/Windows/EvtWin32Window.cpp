#include "EvtWin32Window.h"

std::string keg::WindowsWindow::windowClassName = "ChthollyWindow";
std::unordered_map<HWND, keg::EvtWin32Delegate*> keg::EvtWin32Window::win32DelegateMap;

LRESULT keg::EvtWin32Window::WindowMsgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    return win32DelegateMap.count(hWnd) ? 
        win32DelegateMap[hWnd]->WindowMsgCallBack(hWnd, Msg, wParam, lParam) : 
        DefWindowProc(hWnd, Msg, wParam, lParam);
}
