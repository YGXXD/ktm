#include "MetalGraphicsContext.h"
#include "Log/Logger.h"

#import <AppKit/AppKit.h>

id<MTLDevice> ktl::MetalGraphicsContext::gpuDevice;
id<MTLCommandQueue> ktl::MetalGraphicsContext::gpuCmdQueue;

void ktl::MetalGraphicsContext::MetalInit()
{
	@autoreleasepool
	{
		gpuDevice = MTLCreateSystemDefaultDevice();
		assert(gpuDevice != nil);
		gpuCmdQueue = [gpuDevice newCommandQueueWithMaxCommandBufferCount:1];
		assert(gpuDevice != nil);
	}
}

void ktl::MetalGraphicsContext::MetalQuit()
{
	@autoreleasepool
	{
		[gpuCmdQueue autorelease];
		[gpuDevice autorelease];
	}
}

ktl::MetalGraphicsContext::MetalGraphicsContext(void* window)
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

ktl::MetalGraphicsContext::~MetalGraphicsContext()
{
	[metalLayer release];
}

void ktl::MetalGraphicsContext::SwapBuffer()
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
