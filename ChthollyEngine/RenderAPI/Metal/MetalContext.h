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

	inline static id<MTLDevice> GetDevice() { return gpuDevice; }
	inline static id<MTLCommandQueue> GetCmdQueue() { return gpuCmdQueue; }

private:
	static id<MTLDevice> gpuDevice;
	static id<MTLCommandQueue> gpuCmdQueue;

public:
	MetalContext(void* window);
	virtual ~MetalContext();
	virtual void SwapBuffer() override;
 
private:
	CAMetalLayer* metalLayer;		
};
}

#endif
