#include "GraphicsContext.h"

#if defined(CHTHOLLY_RENDER_API_METAL)
keg::GraphicsAPI keg::GraphicsContext::sAPI = keg::GraphicsAPI::Metal;
#elif defined(CHTHOLLY_RENDER_API_VULKAN)
keg::GraphicsAPI keg::GraphicsContext::sAPI = keg::GraphicsAPI::Vulkan;
#elif defined(CHTHOLLY_RENDER_API_DX12)
keg::GraphicsAPI keg::GraphicsContext::sAPI = keg::GraphicsAPI::DX12;
#endif

#ifdef CHTHOLLY_RENDER_API_METAL
	#include "Metal/MetalContext.h"
#endif
#ifdef CHTHOLLY_RENDER_API_VULKAN
	#include "Vulkan/VulkanContext.h"
#endif
#ifdef CHTHOLLY_RENDER_API_DX12
	#include "DirectX12/DirectX12Context.h"
#endif

void keg::GraphicsContext::Init()
{
	switch(sAPI) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case GraphicsAPI::Metal: MetalContext::MetalInit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case GraphicsAPI::DX12: DirectX12Context::DirectX12Init(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case GraphicsAPI::Vulkan: VulkanContext::VulkanInit(); break;
#endif
		default: assert(false); break;
	}
}

void keg::GraphicsContext::Quit()
{
	switch(sAPI) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case GraphicsAPI::Metal: MetalContext::MetalQuit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case GraphicsAPI::DX12: DirectX12Context::DirectX12Quit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case GraphicsAPI::Vulkan: VulkanContext::VulkanQuit(); break;
#endif
		default: assert(false); break;
	}
}
