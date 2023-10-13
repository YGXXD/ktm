#include "EvtNSWindow.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/AppEvent.h"

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
}

- (void)windowWillClose:(NSNotification *)notification 
{
	keg::WindowCloseEvent e;
	evtDelegate->GetEventCallback()(e);	
}

- (void)windowDidResize:(NSNotification *)notification 
{
	keg::WindowResizeEvent e(self.frame.size.width, self.frame.size.height);
	evtDelegate->GetEventCallback()(e);
}

- (void)keyDown:(NSEvent *)event
{
    keg::KeyPressedEvent e(event.keyCode, event.isARepeat);
    evtDelegate->GetEventCallback()(e);
}

- (void)keyUp:(NSEvent *)event 
{
	keg::KeyReleasedEvent e(event.keyCode);
    evtDelegate->GetEventCallback()(e); 
}

- (void)mouseDown:(NSEvent *)event 
{
	keg::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)rightMouseDown:(NSEvent *)event 
{
    keg::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)otherMouseDown:(NSEvent *)event 
{
    keg::MouseButtonPressedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)mouseUp:(NSEvent *)event 
{
	keg::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

-(void)rightMouseUp:(NSEvent *)event 
{
    keg::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)otherMouseUp:(NSEvent *)event 
{
    keg::MouseButtonReleasedEvent e(event.buttonNumber);
    evtDelegate->GetEventCallback()(e);
}

- (void)scrollWheel:(NSEvent *)event 
{
    keg::MouseScrolledEvent e(event.deltaX, event.deltaY);
    evtDelegate->GetEventCallback()(e);
}

- (void)mouseMoved:(NSEvent *)event 
{
	NSPoint p = [event locationInWindow];
    if(NSPointInRect(p, self.contentView.bounds))
    {
        keg::MouseMovedEvent e(p.x, p.y);
	    evtDelegate->GetEventCallback()(e);
    }
}

@end
