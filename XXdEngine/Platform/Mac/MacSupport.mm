#include "MacSupport.h"
#include "Log/Logger.h"

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