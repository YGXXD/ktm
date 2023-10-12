#ifndef _VULKAN_GRAPHICS_CONTEXT_H_
#define _VULKAN_GRAPHICS_CONTEXT_H_

#include "Renderer/GraphicsContext.h"
#include <vulkan/vulkan.h>

namespace keg
{
class VulkanContext : public GraphicsContext
{
public: 
	static void VulkanInit();
	static void VulkanQuit();

    VulkanContext(void* window);
    virtual ~VulkanContext();

    virtual void SwapBuffer();

private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice logicDevice;

    VkQueue graphicsQueue;
    VkQueue transferQueue;

    std::unordered_map<uint8_t, VkCommandPool> commandPoolMap;
};
}

#endif