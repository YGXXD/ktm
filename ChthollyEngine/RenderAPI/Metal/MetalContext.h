#ifndef _METAL_GRAPHICS_CONTEXT_H_
#define _METAL_GRAPHICS_CONTEXT_H_

#include "Basic/Basic.h"

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

namespace keg
{
class MetalContext final
{
public: 
	static void MetalInit();
	static void MetalQuit();

	static CHTHOLLY_INLINE id<MTLDevice> GetDevice() { return device; }
	static CHTHOLLY_INLINE id<MTLCommandQueue> GetCmdQueue() { return cmdQueue; }

private:
	static id<MTLDevice> device;
	static id<MTLCommandQueue> cmdQueue;
};
}

#endif
