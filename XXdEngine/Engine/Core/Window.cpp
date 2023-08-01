#include "Window.hpp"

#if defined(XXD_PLATFORM_APPLE)
    #include "Mac/MacWindow.hpp"
#elif defined(XXD_PLATFORM_WINDOWS)

#endif

xxd::Window* xxd::Window::Create(const WindowProps &props)
{
    return nullptr;
}