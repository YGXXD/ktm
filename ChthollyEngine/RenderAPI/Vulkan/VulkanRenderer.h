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
    void CreateSurface(void* window);
    void CreateSwapChain();
    void CreateRenderTargetView();
    void CreateRenderPass();
    void CreateFrameBuffers();
    void CreateFence();

    VkSurfaceKHR surface;

    uint32_t swapChainWidth;
	uint32_t swapChainHeight;
    uint32_t swapChainCount;
    VkFormat renderTargetFormat;
    VkFormat depthStencilFormat;
    VkSwapchainKHR swapChain;
    
    std::vector<VkImage> renderTargetImages;
	std::vector<VkImageView> renderTargetViews;

    VkImage depthStencilImage;
    VkImageView depthStencilView;

    VkRenderPass renderPass;
    std::vector<VkFramebuffer> frameBuffers;

    VkFence renderFence;
};
}

#endif