#ifndef _VULKAN_RENDERER_H_
#define _VULKAN_RENDERER_H_

#include "Render/Renderer.h"
#include <vulkan/vulkan.h>

namespace keg
{
class VulkanRenderer : public Renderer
{
public:
    VulkanRenderer(void* window);
    virtual ~VulkanRenderer();

    virtual void SwapBuffer();
private:
    VkSurfaceKHR surface;

    uint32_t swapChainWidth;
	uint32_t swapChainHeight;
    uint32_t swapChainCount;
    VkFormat renderTargetFormat;
    VkFormat depthStencilFormat;
    VkSwapchainKHR swapChain;
    
    std::vector<VkImage> renderTargetImages;
	std::vector<VkImageView> renderTargetViews;

    VkFence renderFence;
};
}

#endif