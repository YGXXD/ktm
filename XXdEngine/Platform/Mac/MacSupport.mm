#include "MacSupport.h"
#include "Log/Logger.h"

@implementation NSApplication(Debug)

- (void)dealloc 
{
    [super dealloc];
    XXD_FATAL("CocoaApp销毁")
}

@end

bool xxd::MacSupport::bisInitialized = false;

void xxd::MacSupport::MacCocoaInit()
{
    assert(!bisInitialized && NSApp == nil);
    bisInitialized = true;
    @autoreleasepool
    {
        auto cocoaApp = [[NSApplication sharedApplication] autorelease];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp finishLaunching];
        [NSApp activateIgnoringOtherApps:true];
    }
}

void xxd::MacSupport::MacCocoaPollEvent()
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

void xxd::MacSupport::MacCocoaQuit()
{
    assert(NSApp != nil && bisInitialized);
    bisInitialized = false;
    @autoreleasepool
    {
        [NSApp release];
        NSApp = nil;
    }
}

@implementation EvtNSWindow

@synthesize eventCallback;

- (instancetype)init 
{
    self = [super init];
    if(self != nil)
    {
        [self setDelegate:self];
    }
    return self;
}

- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag screen:(NSScreen *)screen 
{
    self = [super initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag screen:screen];
    if(self != nil)
    {
        [self setDelegate:self];
    }
    return self;
}

- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag 
{
    self = [super initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag];
    if(self != nil)
    {
        [self setDelegate:self];
    }
    return self;
}

- (void)dealloc 
{
    [super dealloc];
    XXD_DEBUG("窗口销毁")
}

- (void)windowWillClose:(NSNotification *)notification 
{
    XXD_DEBUG("窗口关闭")
}

- (void)windowDidResize:(NSNotification *)notification 
{
    XXD_DEBUG("窗口大小改变")
}

- (void)keyDown:(NSEvent *)event 
{
    XXD_DEBUG("Key");
}

- (void)mouseDown:(NSEvent *)event 
{
    XXD_DEBUG("MouseDown");
}

- (void)mouseUp:(NSEvent *)event 
{
    XXD_DEBUG("MouseUp");
}

@end