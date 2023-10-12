#include "VulkanContext.h"

VkInstance keg::VulkanContext::instance;
VkPhysicalDevice keg::VulkanContext::physicalDevice;

VkDevice keg::VulkanContext::device;
VkQueue keg::VulkanContext::graphicsQueue;
VkQueue keg::VulkanContext::transferQueue;
VkQueue keg::VulkanContext::computeQueue;

std::unordered_map<VkQueue, uint32_t> keg::VulkanContext::queueFamilyIndexMap;
std::unordered_map<VkQueue, VkCommandPool> keg::VulkanContext::queueCmdPoolMap;

void keg::VulkanContext::VulkanInit()
{
    CreateVulkanInstance();
    SelectPhysicalDevice();
    CreateLogicDeviceAndQueue();
	CreateCommandPool();
}

void keg::VulkanContext::VulkanQuit()
{
	for(const auto& pair : queueCmdPoolMap)
	{
		vkDestroyCommandPool(device, pair.second, nullptr);
	}
	vkDestroyDevice(device, nullptr);
	vkDestroyInstance(instance, nullptr);
}

void keg::VulkanContext::CreateVulkanInstance()
{
	// 创建Vulkan实例
	VkApplicationInfo appInfo = { };
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pApplicationName = "Chtholly";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Chtholly";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    std::vector<const char*> instanceExtensionNames;
	std::vector<const char*> instanceLayerNames;
	VkInstanceCreateFlags instanceCreateFlags = 0;

	instanceExtensionNames.push_back("VK_KHR_get_physical_device_properties2");
	instanceExtensionNames.push_back("VK_KHR_surface");
#if defined(CHTHOLLY_PLATFORM_APPLE)
	// Apple官方不支持Vulkan, 通过MoltenVK在Apple平台运行Vulkan
	instanceExtensionNames.push_back("VK_KHR_portability_enumeration"); 
	instanceCreateFlags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
	// 开启MacOS扩展和Metal扩展
	instanceExtensionNames.push_back("VK_MVK_macos_surface");
    instanceExtensionNames.push_back("VK_EXT_metal_surface");
#endif
	instanceLayerNames.push_back("VK_LAYER_KHRONOS_validation");
	
	VkInstanceCreateInfo instCreateInfo = { };
	instCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;	
	instCreateInfo.pApplicationInfo = &appInfo;
	instCreateInfo.enabledExtensionCount = instanceExtensionNames.size();
	instCreateInfo.ppEnabledExtensionNames = instanceExtensionNames.data();
	instCreateInfo.enabledLayerCount = instanceLayerNames.size();
	instCreateInfo.ppEnabledLayerNames = instanceLayerNames.data();
	instCreateInfo.flags = instanceCreateFlags;

	vkCreateInstance(&instCreateInfo, nullptr, &instance);
    assert(instance);
}

void keg::VulkanContext::SelectPhysicalDevice()
{
    // 获取物理显示设备
	uint32_t enumPhysicalDevicesNum;
	vkEnumeratePhysicalDevices(instance, &enumPhysicalDevicesNum, nullptr);

	std::vector<VkPhysicalDevice> enumPhysicalDevices(enumPhysicalDevicesNum);
	vkEnumeratePhysicalDevices(instance, &enumPhysicalDevicesNum, enumPhysicalDevices.data());

	for(const auto& pd : enumPhysicalDevices)
	{
		VkPhysicalDeviceProperties pdProperties;
		vkGetPhysicalDeviceProperties(pd, &pdProperties);
		if(pdProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) // 判断是否是独立显卡
		{
			physicalDevice = pd;	
		}
	}
	if(!physicalDevice)
	{
		physicalDevice = enumPhysicalDevices[0];
	}
	assert(physicalDevice);
}

void keg::VulkanContext::CreateLogicDeviceAndQueue()
{
	// 获取队列族, 枚举并选择队列族
	uint32_t pdQueueFamilyPropertiesNum;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pdQueueFamilyPropertiesNum, nullptr);
    std::vector<VkQueueFamilyProperties> pdQueueFamilyProperties(pdQueueFamilyPropertiesNum);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pdQueueFamilyPropertiesNum, pdQueueFamilyProperties.data());

	uint32_t graphicsQueueFamilyIndex = -1u, transferQueueFamilyIndex = -1u, computeQueueFamilyIndex = -1u;
    for(uint32_t i = 0; i < pdQueueFamilyPropertiesNum; i++)	
    {
        if(pdQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && graphicsQueueFamilyIndex == -1u)
        {
			graphicsQueueFamilyIndex = i;
        }
		if(pdQueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT && transferQueueFamilyIndex == -1u)
        {
			transferQueueFamilyIndex = i;
        }	
		if(pdQueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT && computeQueueFamilyIndex == -1u)
        {
			computeQueueFamilyIndex = i;
        }

		if(graphicsQueueFamilyIndex != -1u && transferQueueFamilyIndex != -1u && computeQueueFamilyIndex != -1u)
		{
			break;
		}
    }

	std::set<uint32_t> queueFamilyIndexSet;
	queueFamilyIndexSet.insert(graphicsQueueFamilyIndex);
	queueFamilyIndexSet.insert(transferQueueFamilyIndex);
	queueFamilyIndexSet.insert(computeQueueFamilyIndex);

	// 创建逻辑设备队列
	float deviceQueuePriorities = 1.f;
	std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos(queueFamilyIndexSet.size());
	{
		int i = 0;
		for(const auto& index : queueFamilyIndexSet)
		{
			deviceQueueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueCreateInfos[i].queueFamilyIndex = index;
			deviceQueueCreateInfos[i].queueCount = 1;
			deviceQueueCreateInfos[i].pQueuePriorities = &deviceQueuePriorities;
			++i;
		}
	} 
	
	std::vector<const char*> deviceExtensionNames;
	// 创建逻辑设备
	deviceExtensionNames.push_back("VK_KHR_portability_subset");
	deviceExtensionNames.push_back("VK_KHR_swapchain");

	VkPhysicalDeviceFeatures pdFeatures;
	vkGetPhysicalDeviceFeatures(physicalDevice, &pdFeatures);
	
	VkPhysicalDeviceFeatures enableFeatures = { };
	enableFeatures.samplerAnisotropy = pdFeatures.samplerAnisotropy;
	enableFeatures.multiDrawIndirect = pdFeatures.multiDrawIndirect;
	enableFeatures.tessellationShader = pdFeatures.geometryShader;
	enableFeatures.geometryShader = pdFeatures.geometryShader;
	enableFeatures.fillModeNonSolid = pdFeatures.fillModeNonSolid;

	VkDeviceCreateInfo deviceCreateInfo = { };
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = deviceQueueCreateInfos.size();
	deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();
	deviceCreateInfo.pEnabledFeatures = &enableFeatures; 
	deviceCreateInfo.enabledExtensionCount = deviceExtensionNames.size();
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensionNames.data();

	vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
	assert(device);

	// 从逻辑设备中获取队列
	vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &graphicsQueue);
	assert(graphicsQueue);
	queueFamilyIndexMap[graphicsQueue] = graphicsQueueFamilyIndex;

	vkGetDeviceQueue(device, transferQueueFamilyIndex, 0, &transferQueue);
	assert(transferQueue);
	queueFamilyIndexMap[transferQueue] = transferQueueFamilyIndex;

	vkGetDeviceQueue(device, computeQueueFamilyIndex, 0, &computeQueue);
	assert(computeQueue);
	queueFamilyIndexMap[computeQueue] = computeQueueFamilyIndex;
}

void keg::VulkanContext::CreateCommandPool()
{
	for(const auto& pair : queueFamilyIndexMap)
	{
		VkCommandPoolCreateInfo cmdPoolCreateInfo = { };
		cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cmdPoolCreateInfo.queueFamilyIndex = pair.second;
		cmdPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		vkCreateCommandPool(device, &cmdPoolCreateInfo, nullptr, &queueCmdPoolMap[pair.first]);
	}
}

keg::VulkanContext::VulkanContext(void* window)
{
	
}

keg::VulkanContext::~VulkanContext()
{
    
}

void keg::VulkanContext::SwapBuffer()
{

}