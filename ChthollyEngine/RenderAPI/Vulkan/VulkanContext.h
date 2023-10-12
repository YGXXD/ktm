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

    CHTHOLLY_INLINE VkDevice GetDevice() { return device; }
    CHTHOLLY_INLINE VkQueue GetGrapicsQueue() { return graphicsQueue; }
    CHTHOLLY_INLINE VkQueue GetTransferQueue() { return transferQueue; }
    CHTHOLLY_INLINE VkQueue GetComputeQueue() { return computeQueue; }

    CHTHOLLY_INLINE VkCommandPool GetGrapicsCmdPool() { return queueCmdPoolMap[graphicsQueue]; }
    CHTHOLLY_INLINE VkCommandPool GetTransferCmdPool() { return queueCmdPoolMap[transferQueue]; }
    CHTHOLLY_INLINE VkCommandPool GetComputeCmdPool() { return queueCmdPoolMap[computeQueue]; } 

private:
    static void CreateVulkanInstance();
    static void SelectPhysicalDevice();
    static void CreateLogicDeviceAndQueue();
    static void CreateCommandPool();

    static VkInstance instance;
    static VkPhysicalDevice physicalDevice;
     
    static VkDevice device;
    static VkQueue graphicsQueue;
    static VkQueue transferQueue;
    static VkQueue computeQueue;

    static std::unordered_map<VkQueue, uint32_t> queueFamilyIndexMap;
    static std::unordered_map<VkQueue, VkCommandPool> queueCmdPoolMap;

    VkSurfaceKHR surface;
};
}

#endif