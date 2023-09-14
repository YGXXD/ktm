#include "EvtWin32Window.h"

std::unordered_map<HWND, ktl::EvtWin32Delegate*> ktl::EvtWin32Window::win32DelegateMap;

LRESULT ktl::EvtWin32Window::WindowMsgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    return win32DelegateMap.count(hWnd) ? 
        win32DelegateMap[hWnd]->WindowMsgCallBack(hWnd, Msg, wParam, lParam) : 
        DefWindowProc(hWnd, Msg, wParam, lParam);
}
