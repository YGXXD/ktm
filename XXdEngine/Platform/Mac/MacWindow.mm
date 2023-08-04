#include "MacWindow.h"
#include "Log/Logger.h"
#include "Event/Delegate.h"
#include "MacSupport.h"

xxd::MacWindow::MacWindow(const WindowProps& props)
{
    Init(props);
}

xxd::MacWindow::~MacWindow()
{
    MacSupport::MacCocoaQuit();
}

void xxd::MacWindow::Init(const WindowProps& props)
{
    MacSupport::MacCocoaInit();
    @autoreleasepool
    {
        NSRect rect;
        rect.origin.x = 100;
        rect.origin.y = 100;
        rect.size.width = props.width;
        rect.size.height = props.height;

        window = [[EvtNSWindow alloc] initWithContentRect:rect 
            styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable 
            backing:NSBackingStoreBuffered defer:false];

        NSString* title = [[[NSString alloc] initWithUTF8String:props.title.c_str()] autorelease];
        [window setTitle:title];
        [window makeKeyWindow];
        [window orderFrontRegardless];
        [window setBackgroundColor:NSColor.whiteColor];
    }
}

void xxd::MacWindow::OnUpdate()
{
    MacSupport::MacCocoaPollEvent();
}

uint32_t xxd::MacWindow::GetWidth() const
{
    return width;
}

uint32_t xxd::MacWindow::GetHeight() const
{
    return height;
}

void xxd::MacWindow::SetEventCallback(void(* callback)(Event&))
{
    if(window != nil)
        window.eventCallback.BindFunction(callback);
}

void xxd::MacWindow::SetVSync(bool enabled)
{

}

bool xxd::MacWindow::IsVSync() const
{
    return false;
}

void* xxd::MacWindow::GetNativeWindow() const
{
    return (__bridge void*)window;
}
