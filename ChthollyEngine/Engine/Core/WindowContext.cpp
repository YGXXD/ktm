#include "WindowContext.h"

#if defined(CHTHOLLY_PLATFORM_APPLE)
    #include "Mac/MacCocoaContext.h"
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
    #include "Windows/WindowsWin32Context.h"
#endif

void keg::WindowContext::Init()
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacCocoaContext::MacCocoaInit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	WindowsWin32Context::WindowsWin32Init();
#endif 
}

void keg::WindowContext::PollEvent()
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
    MacCocoaContext::MacCocoaPollEvent();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	WindowsWin32Context::WindowsWin32PollEvent();
#endif 
}

void keg::WindowContext::Quit()
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
	MacCocoaContext::MacCocoaQuit();
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	WindowsWin32Context::WindowsWin32Quit();
#endif 
}