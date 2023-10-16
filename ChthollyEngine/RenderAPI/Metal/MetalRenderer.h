#ifndef _METAL_RENDERER_H_
#define _METAL_RENDERER_H_

#include "Render/Renderer.h"

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

namespace keg
{
class MetalRenderer : public Renderer
{
public:
	MetalRenderer(void* window);
	virtual ~MetalRenderer();
	virtual void SwapBuffer() override;
 
private:
	CAMetalLayer* metalLayer;
	id<MTLFence> renderFence;
};
}

#endif