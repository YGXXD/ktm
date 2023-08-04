#ifndef _MAC_SUPPORT_H_
#define _MAC_SUPPORT_H_

namespace xxd
{
class MacSupport
{
public:
    MacSupport() = delete;
    static void MacCocoaInit();
    static void MacCocoaPollEvent();
    static void MacCocoaQuit();
    
    inline static bool IsInitialized() { return bisInitialized; }
private:
    static bool bisInitialized;
};
}

#include "Event/Delegate.h"
#include "Event/Event.h"

#import <AppKit/AppKit.h>

@interface EvtNSWindow : NSWindow <NSWindowDelegate>

@property (readonly) xxd::SingleDelegate<void, xxd::Event&> eventCallback;

@end

#endif