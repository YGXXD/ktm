#include "MacWindow.h"
#include "Log/Logger.h"
#include "Event/Delegate.h"

#import <AppKit/AppKit.h>

@interface MacWindowDelegate : NSObject<NSWindowDelegate>

@property(readonly) xxd::SingleDelegate<void, xxd::Event&> eventCallback;

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

@implementation NSWindow (Event)

- (void)keyDown:(NSEvent *)event 
{
    [super keyDown:event];
    DEBUG_LOG("Key");
}

- (void)mouseDown:(NSEvent *)event 
{
    DEBUG_LOG("MouseDown");
    
}

- (void)mouseUp:(NSEvent *)event 
{
     DEBUG_LOG("MouseUp");
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
    [NSApplication sharedApplication]; 
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp finishLaunching];
    [NSApp activateIgnoringOtherApps:true];

    NSRect rect;
    rect.origin.x = 100;
    rect.origin.y = 100;
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
        del.eventCallback.BindFunction(callback);
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
