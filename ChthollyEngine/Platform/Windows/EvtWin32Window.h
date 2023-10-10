#ifndef _EVT_WIN32_WINDOW_H_
#define _EVT_WIN32_WINDOW_H_

#include <windows.h>
#include <unordered_map>

namespace keg
{
class EvtWin32Delegate
{
public:
	virtual LRESULT WindowMsgCallBack(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
};

class EvtWin32Window
{
public:
    static LRESULT WindowMsgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
    static std::unordered_map<HWND, EvtWin32Delegate*> win32DelegateMap;
};

}

#endif