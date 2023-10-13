#include "Window.h"

#if defined(CHTHOLLY_PLATFORM_APPLE)
    #include "Mac/MacWindow.h"
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
    #include "Windows/WindowsWindow.h"
#endif

keg::Window* keg::Window::Create(const WindowProps& props)
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    return new MacWindow(props);
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	return new WindowsWindow(props);
#endif 
}


