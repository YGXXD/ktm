#include "Window.h"

#if defined(CHTHOLLY_PLATFORM_APPLE)
    #include "Mac/MacWindow.h"
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
    #include "Windows/WindowsWindow.h"
#endif

bool keg::Window::bisInitialized = false;

keg::Window* keg::Window::Create(const WindowProps& props)
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    return new MacWindow(props);
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	return new WindowsWindow(props);
#endif 
}

void keg::Window::Init()
{
    assert(!bisInitialized);
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacWindow::MacCocoaInit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	WindowsWindow::WindowsWin32Init();
#endif 
    bisInitialized = true;
}

void keg::Window::PollEvent()
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacWindow::MacCocoaPollEvent();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	WindowsWindow::WindowsWin32PollEvent();
#endif 
}

void keg::Window::Quit()
{
    assert(bisInitialized);
#if defined(CHTHOLLY_PLATFORM_APPLE)
	MacWindow::MacCocoaQuit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	WindowsWindow::WindowsWin32Quit();
#endif 
    bisInitialized = false;
}
