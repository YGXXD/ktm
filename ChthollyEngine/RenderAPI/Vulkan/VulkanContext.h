#ifndef _VULKAN_GRAPHICS_CONTEXT_H_
#define _VULKAN_GRAPHICS_CONTEXT_H_

#include "Basic/SetupBase.h"
#include <vulkan/vulkan.h>

namespace keg
{

class VulkanContext final
{
public: 
	static void VulkanInit();
	static void VulkanQuit();

    static CHTHOLLY_INLINE VkInstance GetInstance() { return instance; }
    static CHTHOLLY_INLINE VkPhysicalDevice GetPhysicalDevice() { return physicalDevice; }
    static CHTHOLLY_INLINE VkDevice GetDevice() { return device; }
    static CHTHOLLY_INLINE VkQueue GetGrapicsQueue() { return graphicsQueue; }
    static CHTHOLLY_INLINE VkQueue GetTransferQueue() { return transferQueue; }
    static CHTHOLLY_INLINE VkQueue GetComputeQueue() { return computeQueue; }

    static CHTHOLLY_INLINE VkCommandPool GetGrapicsCmdPool() { return queueCmdPoolMap[graphicsQueue]; }
    static CHTHOLLY_INLINE VkCommandPool GetTransferCmdPool() { return queueCmdPoolMap[transferQueue]; }
    static CHTHOLLY_INLINE VkCommandPool GetComputeCmdPool() { return queueCmdPoolMap[computeQueue]; } 

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

};
}

#endif