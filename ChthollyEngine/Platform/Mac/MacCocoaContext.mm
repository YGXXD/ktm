#include "MacCocoaContext.h"

#import <AppKit/AppKit.h>

void keg::MacCocoaContext::MacCocoaInit()
{
	assert(NSApp == nil);
    @autoreleasepool
    {
        auto cocoaApp = [[NSApplication sharedApplication] autorelease];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp finishLaunching];
        [NSApp activateIgnoringOtherApps:true];
    }
}

void keg::MacCocoaContext::MacCocoaPollEvent()
{
    @autoreleasepool
    {
        while(true)
        {   
            // nil 会指定 [NSDate distantPast]
            NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:true];
            if(event == nil)
                break;
            [NSApp sendEvent:event];
        }
    }
}

void keg::MacCocoaContext::MacCocoaQuit()
{
    assert(NSApp != nil);
    @autoreleasepool
    {
        [NSApp release];
        NSApp = nil;
    }
}