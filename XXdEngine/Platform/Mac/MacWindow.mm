#include "MacWindow.h"
#include "Log/Logger.h"
#include "Core/Delegate.h"

#import <AppKit/AppKit.h>

DECLARE_FUNCTION_DELEGATE(PoolEventDelegate, void, xxd::Event&)

@interface MacWindowDelegate : NSObject<NSWindowDelegate>

@property(readonly) PoolEventDelegate pollEvent;

@end

@implementation MacWindowDelegate
- (void)windowWillClose:(NSNotification *)notification
{
    DEBUG_LOG("窗口关闭");
}

- (void)windowDidResize:(NSNotification *)notification 
{
    DEBUG_LOG("窗口大小改变");
}

@end

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
    [window setBackgroundColor:NSColor.whiteColor];

    MacWindowDelegate* del = [[MacWindowDelegate alloc] init];
    [window setDelegate:del];

}

void xxd::MacWindow::OnUpdate()
{
    // nil 会指定 [NSDate distantPast]
    NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:true];

    while(event != nil)
    {
        [NSApp sendEvent:event];
        event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:true];
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
    MacWindowDelegate* del = (MacWindowDelegate*)window.delegate;
    if(del != nil)
        del.pollEvent.BindFunction(callback);
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