#include "MacWindow.h"

keg::MacWindow::MacWindow(const WindowProps& props)
{
    InitProps(props);
}

keg::MacWindow::~MacWindow()
{
	[window release];
}

keg::EventCallbackDelegate& keg::MacWindow::GetEventCallback()
{
	return eventCallback;
}

void keg::MacWindow::InitProps(const WindowProps& props)
{
    @autoreleasepool
    {
        title = props.title;

        NSRect rect;
        rect.origin.x = 100;
        rect.origin.y = 100;
        rect.size.width = props.width;
        rect.size.height = props.height;

        window = [[EvtNSWindow alloc] initWithContentRect:rect 
            styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable 
            backing:NSBackingStoreBuffered defer:false];
		window.releasedWhenClosed = false;
		window.evtDelegate = this;
	
        NSString* nsTitle = [[[NSString alloc] initWithUTF8String:title.c_str()] autorelease];
        [window setTitle:nsTitle];
        [window makeKeyWindow];
        [window orderFrontRegardless];
        [window setBackgroundColor:NSColor.whiteColor];
    }
}

void keg::MacWindow::OnUpdate()
{

}

uint32_t keg::MacWindow::GetWidth() const
{
    return window.contentView.frame.size.width;
}

uint32_t keg::MacWindow::GetHeight() const
{
    return window.contentView.frame.size.height;
}

void keg::MacWindow::SetVSync(bool enabled)
{

}

bool keg::MacWindow::IsVSync() const
{
    return false;
}

void* keg::MacWindow::GetNativeWindow() const
{
    return (__bridge void*)window;
}
