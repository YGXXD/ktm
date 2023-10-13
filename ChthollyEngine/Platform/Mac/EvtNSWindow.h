#ifndef _MAC_SUPPORT_H_
#define _MAC_SUPPORT_H_

#include "Core/Window.h"

namespace keg
{
class EvtNSDelegate
{
public:
	virtual EventCallbackDelegate& GetEventCallback() = 0;
};
}

#import <AppKit/AppKit.h>

@interface EvtNSWindow : NSWindow <NSWindowDelegate>

@property (assign, readwrite) keg::EvtNSDelegate* evtDelegate;

@end

#endif
