#include "MacWindow.h"
#include "Log/Logger.h"

void keg::MacWindow::MacCocoaInit()
{
	assert(NSApp == nil);
    @autoreleasepool
    {
        auto cocoaApp = [[NSApplication sharedApplication] autorelease];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp finishLaunching];
        [NSApp activateIgnoringOtherApps:true];
    }
}

void keg::MacWindow::MacCocoaPollEvent()
{
    @autoreleasepool
    {
        while(true)
        {   
            // nil 会指定 [NSDate distantPast]
            NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:true];
            if(event == nil)
                break;
            [NSApp sendEvent:event];
        }
    }
}

void keg::MacWindow::MacCocoaQuit()
{
    assert(NSApp != nil);
    @autoreleasepool
    {
        [NSApp release];
        NSApp = nil;
    }
}

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
