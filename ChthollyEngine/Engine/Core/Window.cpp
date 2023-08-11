#include "Window.h"

#if defined(CHTHOLLY_PLATFORM_APPLE)
    #include "Mac/MacWindow.h"
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)

#endif

bool xxd::Window::bisInitialized = false;

xxd::Window* xxd::Window::Create(const WindowProps& props)
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    return new MacWindow(props);
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
}

void xxd::Window::Init()
{
    assert(!bisInitialized);
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacWindow::MacCocoaInit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
    bisInitialized = true;
}

void xxd::Window::PollEvent()
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacWindow::MacCocoaPollEvent();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
}

void xxd::Window::Quit()
{
    assert(bisInitialized);
#if defined(CHTHOLLY_PLATFORM_APPLE)
	MacWindow::MacCocoaQuit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
    bisInitialized = false;
}
