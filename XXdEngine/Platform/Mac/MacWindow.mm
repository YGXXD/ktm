#include "MacWindow.h"
#include "Log/Logger.h"
#include "Event/Delegate.h"
#include "EvtNSWindow.h"

void xxd::MacWindow::MacCocoaInit()
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

void xxd::MacWindow::MacCocoaPollEvent()
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

void xxd::MacWindow::MacCocoaQuit()
{
    assert(NSApp != nil);
    @autoreleasepool
    {
        [NSApp release];
        NSApp = nil;
    }
}

xxd::MacWindow::MacWindow(const WindowProps& props)
{
    InitProps(props);
}

xxd::MacWindow::~MacWindow()
{

}

void xxd::MacWindow::InitProps(const WindowProps& props)
{
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
