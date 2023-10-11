#ifndef _VULKAN_GRAPHICS_CONTEXT_H_
#define _VULKAN_GRAPHICS_CONTEXT_H_

#include "Renderer/GraphicsContext.h"

namespace keg
{
class VulkanGraphicsContext : public GraphicsContext
{
public: 
	static void VulkanInit();
	static void VulkanQuit();

    VulkanGraphicsContext(void* window);
    virtual ~VulkanGraphicsContext();

    virtual void SwapBuffer();
};
}

#endif