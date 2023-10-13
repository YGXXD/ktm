#include "VulkanRenderer.h"
#include "VulkanContext.h"

#if defined(CHTHOLLY_PLATFORM_APPLE)
	#import <QuartzCore/QuartzCore.h>
	#import <Appkit/AppKit.h>
	#include <vulkan/vulkan_macos.h>
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)

#endif

keg::VulkanRenderer::VulkanRenderer(void* window)
{
#if defined(CHTHOLLY_PLATFORM_APPLE)
	@autoreleasepool
	{
		CAMetalLayer* metalLayer = [[CAMetalLayer layer] autorelease];
		NSView* view = ((NSWindow*)window).contentView;
		view.wantsLayer = true;
		view.layer = metalLayer;
		
		VkMacOSSurfaceCreateInfoMVK surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
        surfaceCreateInfo.pNext = NULL;
        surfaceCreateInfo.flags = 0;
        surfaceCreateInfo.pView = (const void *)view;
        vkCreateMacOSSurfaceMVK(VulkanContext::GetInstance(), &surfaceCreateInfo, NULL, &surface);

		swapChainWidth = view.bounds.size.width;
		swapChainHeight = view.bounds.size.height;
		renderTargetFormat = VK_FORMAT_B8G8R8A8_SRGB;
	}
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)

#endif
	assert(surface);

	VkSurfaceCapabilitiesKHR surfaceCapabilities; 
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VulkanContext::GetPhysicalDevice(), surface, &surfaceCapabilities);

	swapChainCount = 2;
	// 创建交换链
	VkSwapchainCreateInfoKHR swapChainInfo = { };
	swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainInfo.surface = surface;
	swapChainInfo.minImageCount = swapChainCount;	
	swapChainInfo.imageFormat = renderTargetFormat;
	swapChainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapChainInfo.imageExtent.width = swapChainWidth;
	swapChainInfo.imageExtent.height = swapChainHeight;	
	swapChainInfo.imageArrayLayers = 1;
	swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapChainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapChainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	swapChainInfo.clipped = VK_TRUE;
	swapChainInfo.oldSwapchain = swapChain;

	vkCreateSwapchainKHR(VulkanContext::GetDevice(), &swapChainInfo, nullptr, &swapChain);
	assert(swapChain);

	renderTargetImages.resize(swapChainCount);
	vkGetSwapchainImagesKHR(VulkanContext::GetDevice(), swapChain, &swapChainCount, renderTargetImages.data());

	renderTargetViews.resize(swapChainCount);

	for(int i = 0; i < renderTargetViews.size(); i++)
	{
		VkImageViewCreateInfo ImageViewInfo = { };
		ImageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ImageViewInfo.image = renderTargetImages[i];
		ImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		ImageViewInfo.format = renderTargetFormat;
		ImageViewInfo.components = {VK_COMPONENT_SWIZZLE_IDENTITY, 
									VK_COMPONENT_SWIZZLE_IDENTITY,
									VK_COMPONENT_SWIZZLE_IDENTITY,
									VK_COMPONENT_SWIZZLE_IDENTITY};
		ImageViewInfo.subresourceRange.baseMipLevel = 0;
		ImageViewInfo.subresourceRange.levelCount = 1;
		ImageViewInfo.subresourceRange.baseArrayLayer = 0;
		ImageViewInfo.subresourceRange.layerCount = 1;
		ImageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		vkCreateImageView(VulkanContext::GetDevice(), &ImageViewInfo, nullptr, &renderTargetViews[i]);
		assert(renderTargetViews[i]);
	}

	// 创建栅栏
	VkFenceCreateInfo fenceInfo = { };
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	vkCreateFence(VulkanContext::GetDevice(), &fenceInfo, nullptr, &renderFence);
	assert(renderFence);
}

keg::VulkanRenderer::~VulkanRenderer()
{
	vkDestroyFence(VulkanContext::GetDevice(), renderFence, nullptr);
	for(auto& imageView : renderTargetViews)
	{
		vkDestroyImageView(VulkanContext::GetDevice(), imageView, nullptr);
	}
	vkDestroySwapchainKHR(VulkanContext::GetDevice(), swapChain, nullptr);
	vkDestroySurfaceKHR(VulkanContext::GetInstance(), surface, nullptr);
}

void keg::VulkanRenderer::SwapBuffer()
{
	VkDevice device = VulkanContext::GetDevice(); 
	VkQueue graphicsQueue = VulkanContext::GetGrapicsQueue();
	VkCommandPool graphicsCmdPool = VulkanContext::GetGrapicsCmdPool();
	VkCommandBufferAllocateInfo commandBufferInfo = { };
	commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferInfo.commandPool = graphicsCmdPool;
	commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferInfo.commandBufferCount = 1;
	VkCommandBuffer cmdBuffer = nullptr;
	vkAllocateCommandBuffers(device, &commandBufferInfo, &cmdBuffer);
	assert(cmdBuffer);
	vkResetCommandBuffer(cmdBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
	
	uint32_t currIndex;
	vkAcquireNextImageKHR(device, swapChain, 0xffffffff, nullptr, renderFence, &currIndex);
	vkWaitForFences(device, 1, &renderFence, VK_TRUE, 0xffffffff);	
	vkResetFences(device, 1, &renderFence);
	
	VkClearValue ClearValue[1];
	ClearValue[0].color = {0.5f, 1.f, 0.3f, 1.f};

	/*** RenderPass ***/
	/* Attachment */
	std::vector<VkAttachmentDescription> renderAttachmentDescs;

	VkAttachmentDescription renderTargetAttachmentDesc = { };
	renderTargetAttachmentDesc.format = renderTargetFormat;
	renderTargetAttachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
	renderTargetAttachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	renderTargetAttachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	renderTargetAttachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	renderTargetAttachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	renderTargetAttachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	renderTargetAttachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	renderAttachmentDescs.push_back(renderTargetAttachmentDesc);

	VkAttachmentReference renderTargetAttachmentRef = { };
	renderTargetAttachmentRef.attachment = 0;
	renderTargetAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	/* SubPass(设置SubPass依赖的附件) */
	VkSubpassDescription renderSubpassDesc = { };
	renderSubpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	renderSubpassDesc.inputAttachmentCount = 0;
	renderSubpassDesc.pInputAttachments = nullptr;
	renderSubpassDesc.colorAttachmentCount = 1;
	renderSubpassDesc.pColorAttachments = &renderTargetAttachmentRef;
	renderSubpassDesc.pResolveAttachments = nullptr;
	renderSubpassDesc.pDepthStencilAttachment = nullptr;
	renderSubpassDesc.preserveAttachmentCount = 0;
	renderSubpassDesc.pPreserveAttachments = nullptr;

	/* SubPass Dependency(决定SubPass执行顺序) */
	VkSubpassDependency subPassDependency = { };
	subPassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	subPassDependency.dstSubpass = 0; //索引为0的SubPass
	subPassDependency.srcAccessMask = VK_ACCESS_NONE;
	subPassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	subPassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	subPassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

	/* Create RenderPass */
	VkRenderPassCreateInfo renderPassInfo = { };
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = renderAttachmentDescs.size();
	renderPassInfo.pAttachments = renderAttachmentDescs.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &renderSubpassDesc;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &subPassDependency;

	VkRenderPass renderPass = nullptr;
	vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass);
	assert(renderPass);

	VkFramebuffer frameBuffer = nullptr;
	VkImageView AttachImageView[1] = { renderTargetViews[currIndex] };
	VkFramebufferCreateInfo FrameBufferInfo = { };
	FrameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FrameBufferInfo.attachmentCount = 1;
	FrameBufferInfo.pAttachments = AttachImageView;
	FrameBufferInfo.renderPass = renderPass; 
	FrameBufferInfo.width = swapChainWidth;
	FrameBufferInfo.height = swapChainHeight;
	FrameBufferInfo.layers = 1;
	vkCreateFramebuffer(device, &FrameBufferInfo, nullptr, &frameBuffer);
	assert(frameBuffer);

	VkRenderPassBeginInfo renderPassBeginInfo = { };
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.renderPass = renderPass;
	renderPassBeginInfo.framebuffer = frameBuffer;
	renderPassBeginInfo.renderArea = { 0, 0, swapChainWidth, swapChainHeight };; 
	renderPassBeginInfo.clearValueCount = 2;
	renderPassBeginInfo.pClearValues = ClearValue;

	VkCommandBufferBeginInfo BeginInfo = { };
	BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(cmdBuffer, &BeginInfo);
	vkCmdBeginRenderPass(cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdEndRenderPass(cmdBuffer);
	vkEndCommandBuffer(cmdBuffer);

	VkSubmitInfo submitInfo = { };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cmdBuffer;
	vkQueueSubmit(graphicsQueue, 1, &submitInfo, renderFence);

	VkPresentInfoKHR presentInfo = { };
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapChain;
	presentInfo.pImageIndices = &currIndex;
	vkQueuePresentKHR(graphicsQueue, &presentInfo);

	vkWaitForFences(device, 1, &renderFence, VK_TRUE, 0xffffffff);
	vkResetFences(device, 1, &renderFence);
	vkDestroyFramebuffer(device, frameBuffer, nullptr);
	vkDestroyRenderPass(device, renderPass, nullptr);
}