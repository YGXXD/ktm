#include "Window.h"

#if defined(XXD_PLATFORM_APPLE)
    #include "Mac/MacWindow.h"
#elif defined(XXD_PLATFORM_WINDOWS)

#endif

xxd::Window* xxd::Window::Create(const WindowProps& props)
{
    return new xxd::MacWindow(props);
}