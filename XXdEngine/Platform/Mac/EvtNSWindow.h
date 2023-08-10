#ifndef _MAC_SUPPORT_H_
#define _MAC_SUPPORT_H_

#include "Core/Delegate.h"
#include "Event/Event.h"

namespace xxd
{
class EvtNSDelegate
{
public:
	virtual SingleDelegate<void, Event&>& GetEventCallback() = 0;
};
}

#import <AppKit/AppKit.h>

@interface EvtNSWindow : NSWindow <NSWindowDelegate>

@property (assign, readwrite) xxd::EvtNSDelegate* evtDelegate;

@end

#endif
