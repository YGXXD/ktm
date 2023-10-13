#ifndef _WINDOWS_WIN32_CONTEXT_H_
#define _WINDOWS_WIN32_CONTEXT_H_

namespace keg
{
class WindowsWin32Context final
{
public:
    static void WindowsWin32Init();
	static void WindowsWin32PollEvent();
	static void WindowsWin32Quit();
};
}

#endif