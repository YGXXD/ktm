#ifndef _MAC_COCOA_CONTEXT_H_
#define _MAC_COCOA_CONTEXT_H_

namespace keg
{
class MacCocoaContext final
{
public:
    static void MacCocoaInit();
    static void MacCocoaQuit();
    static void MacCocoaPollEvent();
};
}

#endif