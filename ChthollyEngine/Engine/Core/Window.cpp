#include "Window.h"

#if defined(CHTHOLLY_PLATFORM_APPLE)
    #include "Mac/MacWindow.h"
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)

#endif

bool ktl::Window::bisInitialized = false;

ktl::Window* ktl::Window::Create(const WindowProps& props)
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    return new MacWindow(props);
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
}

void ktl::Window::Init()
{
    assert(!bisInitialized);
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacWindow::MacCocoaInit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
    bisInitialized = true;
}

void ktl::Window::PollEvent()
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacWindow::MacCocoaPollEvent();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
}

void ktl::Window::Quit()
{
    assert(bisInitialized);
#if defined(CHTHOLLY_PLATFORM_APPLE)
	MacWindow::MacCocoaQuit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
		
#endif 
    bisInitialized = false;
}
