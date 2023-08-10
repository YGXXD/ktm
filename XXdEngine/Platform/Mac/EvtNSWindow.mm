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

@synthesize eventCallback;

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
	eventCallback(e);	
}

- (void)windowDidResize:(NSNotification *)notification 
{
	xxd::WindowResizeEvent e(self.frame.size.width, self.frame.size.height);
	eventCallback(e);
}

- (void)keyDown:(NSEvent *)event
{
    switch (event.type)
    {
        case NSEventTypeKeyDown: 
	    {
            xxd::KeyPressedEvent e(event.keyCode, event.isARepeat);
            eventCallback(e);
            break;
        }
        case NSEventTypeKeyUp:
	    {
            xxd::KeyPressedEvent e(event.keyCode);
            eventCallback(e);
            break;
        }
        default:
            return;
    }
}

- (void)mouseDown:(NSEvent *)event 
{
	xxd::MouseButtonPressedEvent e(event.buttonNumber);
    eventCallback(e);
}

- (void)rightMouseDown:(NSEvent *)event 
{
    xxd::MouseButtonPressedEvent e(event.buttonNumber);
    eventCallback(e);
}

- (void)otherMouseDown:(NSEvent *)event 
{
    xxd::MouseButtonPressedEvent e(event.buttonNumber);
    eventCallback(e);
}

- (void)mouseUp:(NSEvent *)event 
{
	xxd::MouseButtonReleasedEvent e(event.buttonNumber);
    eventCallback(e);
}

-(void)rightMouseUp:(NSEvent *)event 
{
    xxd::MouseButtonReleasedEvent e(event.buttonNumber);
    eventCallback(e);
}

- (void)otherMouseUp:(NSEvent *)event 
{
    xxd::MouseButtonReleasedEvent e(event.buttonNumber);
    eventCallback(e);
}

- (void)scrollWheel:(NSEvent *)event 
{
    xxd::MouseScrolledEvent e(event.deltaX, event.deltaY);
    eventCallback(e);
}

- (void)mouseMoved:(NSEvent *)event 
{
	NSPoint p = [event locationInWindow];
    if(NSPointInRect(p, self.contentView.bounds))
    {
        xxd::MouseMovedEvent e(p.x, p.y);
	    eventCallback(e);
    }
}

@end
