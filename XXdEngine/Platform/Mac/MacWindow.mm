#include "MacWindow.h"
#import <AppKit/AppKit.h>

xxd::MacWindow::MacWindow(const WindowProps& props)
{
    Init(props);
}

xxd::MacWindow::~MacWindow()
{
    
}

void xxd::MacWindow::Init(const WindowProps& props)
{
    NSRect rect;
    rect.size.width = props.width;
    rect.size.height = props.height;
    window = [[NSWindow alloc] initWithContentRect:rect 
        styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable 
        backing:NSBackingStoreBuffered defer:false];
    NSString* title = [[NSString alloc] initWithUTF8String:props.title.c_str()];
    [window setTitle:title];
    [window makeKeyWindow];
    [window orderFrontRegardless];
    [window setBackgroundColor:NSColor.blueColor];
}

void xxd::MacWindow::OnUpdate()
{
    NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:true];

    while(event != nil)
    {
        [NSApp sendEvent:event];
        event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:true];
    }
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