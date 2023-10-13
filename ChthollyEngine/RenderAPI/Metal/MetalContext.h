#ifndef _METAL_GRAPHICS_CONTEXT_H_
#define _METAL_GRAPHICS_CONTEXT_H_

#include "Renderer/GraphicsContext.h"

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

namespace keg
{
class MetalContext : public GraphicsContext
{
public: 
	static void MetalInit();
	static void MetalQuit();

	static CHTHOLLY_INLINE id<MTLDevice> GetDevice() { return device; }
	static CHTHOLLY_INLINE id<MTLCommandQueue> GetCmdQueue() { return cmdQueue; }

private:
	static id<MTLDevice> device;
	static id<MTLCommandQueue> cmdQueue;

public:
	MetalContext(void* window);
	virtual ~MetalContext();
	virtual void SwapBuffer() override;
 
private:
	CAMetalLayer* metalLayer;		
};
}

#endif
