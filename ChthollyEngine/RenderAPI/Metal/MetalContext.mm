#include "MetalContext.h"

#import <AppKit/AppKit.h>

id<MTLDevice> keg::MetalContext::gpuDevice;
id<MTLCommandQueue> keg::MetalContext::gpuCmdQueue;

void keg::MetalContext::MetalInit()
{
	@autoreleasepool
	{
		gpuDevice = MTLCreateSystemDefaultDevice();
		assert(gpuDevice != nil);
		gpuCmdQueue = [gpuDevice newCommandQueueWithMaxCommandBufferCount:1];
		assert(gpuDevice != nil);
	}
}

void keg::MetalContext::MetalQuit()
{
	@autoreleasepool
	{
		[gpuCmdQueue autorelease];
		[gpuDevice autorelease];
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

		metalLayer.device = gpuDevice; 
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
		id<MTLCommandBuffer> pCmd = [gpuCmdQueue commandBuffer];
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
