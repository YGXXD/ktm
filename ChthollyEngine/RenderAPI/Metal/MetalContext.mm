#include "MetalContext.h"
#include "Log/Logger.h"

#import <AppKit/AppKit.h>

id<MTLDevice> keg::MetalContext::device;
id<MTLCommandQueue> keg::MetalContext::cmdQueue;

void keg::MetalContext::MetalInit()
{
	@autoreleasepool
	{
		device = MTLCreateSystemDefaultDevice();
		assert(device);
		cmdQueue = [device newCommandQueueWithMaxCommandBufferCount:1];
		assert(device);
	}
}

void keg::MetalContext::MetalQuit()
{
	@autoreleasepool
	{
		[cmdQueue autorelease];
		[device autorelease];
	}
}