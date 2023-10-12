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

keg::MetalContext::MetalContext(void* window)
{
	@autoreleasepool
	{
		metalLayer = [CAMetalLayer layer];
		NSView* view = ((NSWindow*)window).contentView;
		view.wantsLayer = true;
		view.layer = [metalLayer retain];

		metalLayer.device = device; 
		metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB; 
		metalLayer.framebufferOnly = true;
		metalLayer.frame = view.bounds;
	}
}

keg::MetalContext::~MetalContext()
{
	[metalLayer release];
}

void keg::MetalContext::SwapBuffer()
{
	@autoreleasepool
	{
		id<CAMetalDrawable> next = [metalLayer nextDrawable];
		id<MTLCommandBuffer> pCmd = [cmdQueue commandBuffer];
    	MTLRenderPassDescriptor* pRpd = [[[MTLRenderPassDescriptor alloc] init] autorelease];
		pRpd.colorAttachments[0].clearColor = MTLClearColorMake(0.5, 1.0, 0.3, 1.0); 
		pRpd.colorAttachments[0].texture = next.texture;
		pRpd.colorAttachments[0].loadAction = MTLLoadActionClear;    	
		pRpd.colorAttachments[0].storeAction = MTLStoreActionStore;

    	id<MTLRenderCommandEncoder> pEnc = [pCmd renderCommandEncoderWithDescriptor:pRpd];
	    
    	[pEnc endEncoding];
    	[pCmd presentDrawable:next];
    	[pCmd commit];
	}	
}
