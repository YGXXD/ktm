#ifndef _MAC_SUPPORT_H_
#define _MAC_SUPPORT_H_

#include "Event/Event.h"

namespace ktl
{
class EvtNSDelegate
{
public:
	virtual class SingleDelegate<void, Event&>& GetEventCallback() = 0;
};
}

#import <AppKit/AppKit.h>

@interface EvtNSWindow : NSWindow <NSWindowDelegate>

@property (assign, readwrite) ktl::EvtNSDelegate* evtDelegate;

@end

#endif
