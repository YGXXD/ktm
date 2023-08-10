#ifndef _MAC_SUPPORT_H_
#define _MAC_SUPPORT_H_

#include "Core/Delegate.h"
#include "Event/Event.h"

#import <AppKit/AppKit.h>

@interface EvtNSWindow : NSWindow <NSWindowDelegate>

@property (assign, readonly) xxd::SingleDelegate<void, xxd::Event&>& eventCallback;

@end

#endif
