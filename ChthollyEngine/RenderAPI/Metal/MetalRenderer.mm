#include "MetalRenderer.h"
#include "MetalContext.h"

#import <Appkit/AppKit.h>

keg::MetalRenderer::MetalRenderer(void* window)
{
	@autoreleasepool
	{
		metalLayer = [CAMetalLayer layer];
		NSView* view = ((NSWindow*)window).contentView;
		view.wantsLayer = true;
		view.layer = metalLayer;
		metalLayer.device = MetalContext::GetDevice(); 
		metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB; 
		metalLayer.framebufferOnly = true;
		metalLayer.drawableSize = [view convertSizeToBacking:view.layer.bounds.size];
	}
}

keg::MetalRenderer::~MetalRenderer()
{
	@autoreleasepool
	{
		[metalLayer autorelease];
	}
}

void keg::MetalRenderer::SwapBuffer()
{
	@autoreleasepool
	{
		id<CAMetalDrawable> next = [metalLayer nextDrawable];
		id<MTLCommandBuffer> pCmd = [MetalContext::GetCmdQueue() commandBuffer];
    	MTLRenderPassDescriptor* pRpd = [[[MTLRenderPassDescriptor alloc] init] autorelease];
		pRpd.colorAttachments[0].clearColor = MTLClearColorMake(0.5f, 1.f, 0.3f, 1.f); 
		pRpd.colorAttachments[0].texture = next.texture;
		pRpd.colorAttachments[0].loadAction = MTLLoadActionClear;    	
		pRpd.colorAttachments[0].storeAction = MTLStoreActionStore;

    	id<MTLRenderCommandEncoder> pEnc = [pCmd renderCommandEncoderWithDescriptor:pRpd];
	    
    	[pEnc endEncoding];
    	[pCmd presentDrawable:next];
    	[pCmd commit];
	}	
}
