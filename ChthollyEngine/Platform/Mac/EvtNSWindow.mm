#include "EvtNSWindow.h"
#include "Log/Logger.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/AppEvent.h"

@implementation NSApplication(Debug)

- (void)dealloc 
{
    [super dealloc];
    KTL_DEBUG("CocoaApp dealloc")
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
    KTL_DEBUG("EvtNSWindow dealloc")
}

- (void)windowWillClose:(NSNotification *)notification 
{
	ktl::WindowCloseEvent e;
	evtDelegate->GetEventCallback()(e);	
}

- (void)windowDidResize:(NSNotification *)notification 
{
	ktl::WindowResizeEvent e(self.frame.size.width, self.frame.size.height);
	evtDelegate->GetEventCallback()(e);
}

- (void)keyDown:(NSEvent *)event
{
    switch (event.type)
    {
        case NSEventTypeKeyDown: 
	    {
            ktl::KeyPressedEvent e(event.keyCode, event.isARepeat);
            evtDelegate->GetEventCallback()(e);
            break;
        }
        case NSEventTypeKeyUp:
	    {
            ktl::KeyPressedEvent e(event.keyCode);
            evtDelegate->GetEventCallback()(e);
            break;
        }
        default:
            return;
    }
}

- (void)mouseDown:(NSEvent *)event 
{
	ktl::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)rightMouseDown:(NSEvent *)event 
{
    ktl::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)otherMouseDown:(NSEvent *)event 
{
    ktl::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)mouseUp:(NSEvent *)event 
{
	ktl::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

-(void)rightMouseUp:(NSEvent *)event 
{
    ktl::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)otherMouseUp:(NSEvent *)event 
{
    ktl::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)scrollWheel:(NSEvent *)event 
{
    ktl::MouseScrolledEvent e(event.deltaX, event.deltaY);
    evtDelegate->GetEventCallback()(e);
}

- (void)mouseMoved:(NSEvent *)event 
{
	NSPoint p = [event locationInWindow];
    if(NSPointInRect(p, self.contentView.bounds))
    {
        ktl::MouseMovedEvent e(p.x, p.y);
	    evtDelegate->GetEventCallback()(e);
    }
}

@end
