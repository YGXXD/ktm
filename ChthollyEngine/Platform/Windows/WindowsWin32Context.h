#ifndef _WINDOWS_WIN32_CONTEXT_H_
#define _WINDOWS_WIN32_CONTEXT_H_

#include <windows.h>
#include "Core/Window.h"

namespace keg
{
class WindowsWin32Context final
{
public:
    static void WindowsWin32Init();
	static void WindowsWin32PollEvent();
	static void WindowsWin32Quit();
    static CHTHOLLY_INLINE const char* GetWindowClassName() { return windowClassName.c_str(); }
private:
    static std::string windowClassName;
};
}

#endif