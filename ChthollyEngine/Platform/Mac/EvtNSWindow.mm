#include "EvtNSWindow.h"
#include "Log/Logger.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/AppEvent.h"

@implementation NSApplication(Debug)

- (void)dealloc 
{
    [super dealloc];
    XXD_DEBUG("CocoaApp dealloc")
}

@end

@implementation EvtNSWindow

@synthesize evtDelegate;

- (instancetype)init 
{
    self = [super init];
    if(self != nil)
    {
        [self setDelegate:self];
		[self setAcceptsMouseMovedEvents:true];
    }
    return self;
}

- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag screen:(NSScreen *)screen 
{
    self = [super initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag screen:screen];
    if(self != nil)
    {
        [self setDelegate:self];
		[self setAcceptsMouseMovedEvents:true];
    }
    return self;
}

- (instancetype)initWithContentRect:(NSRect)contentRect styleMask:(NSWindowStyleMask)style backing:(NSBackingStoreType)backingStoreType defer:(BOOL)flag 
{
    self = [super initWithContentRect:contentRect styleMask:style backing:backingStoreType defer:flag];
    if(self != nil)
    {
        [self setDelegate:self];
		[self setAcceptsMouseMovedEvents:true];
    }
    return self;
}

- (void)dealloc 
{
    [super dealloc];
    XXD_DEBUG("EvtNSWindow dealloc")
}

- (void)windowWillClose:(NSNotification *)notification 
{
	xxd::WindowCloseEvent e;
	evtDelegate->GetEventCallback()(e);	
}

- (void)windowDidResize:(NSNotification *)notification 
{
	xxd::WindowResizeEvent e(self.frame.size.width, self.frame.size.height);
	evtDelegate->GetEventCallback()(e);
}

- (void)keyDown:(NSEvent *)event
{
    switch (event.type)
    {
        case NSEventTypeKeyDown: 
	    {
            xxd::KeyPressedEvent e(event.keyCode, event.isARepeat);
            evtDelegate->GetEventCallback()(e);
            break;
        }
        case NSEventTypeKeyUp:
	    {
            xxd::KeyPressedEvent e(event.keyCode);
            evtDelegate->GetEventCallback()(e);
            break;
        }
        default:
            return;
    }
}

- (void)mouseDown:(NSEvent *)event 
{
	xxd::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)rightMouseDown:(NSEvent *)event 
{
    xxd::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)otherMouseDown:(NSEvent *)event 
{
    xxd::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)mouseUp:(NSEvent *)event 
{
	xxd::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

-(void)rightMouseUp:(NSEvent *)event 
{
    xxd::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)otherMouseUp:(NSEvent *)event 
{
    xxd::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)scrollWheel:(NSEvent *)event 
{
    xxd::MouseScrolledEvent e(event.deltaX, event.deltaY);
    evtDelegate->GetEventCallback()(e);
}

- (void)mouseMoved:(NSEvent *)event 
{
	NSPoint p = [event locationInWindow];
    if(NSPointInRect(p, self.contentView.bounds))
    {
        xxd::MouseMovedEvent e(p.x, p.y);
	    evtDelegate->GetEventCallback()(e);
    }
}

@end
