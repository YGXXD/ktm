#include "GraphicsContext.h"
#include "Renderer.h"

#ifdef CHTHOLLY_RENDER_API_METAL
	#include "Metal/MetalContext.h"
#endif
#ifdef CHTHOLLY_RENDER_API_VULKAN
	#include "Vulkan/VulkanContext.h"
#endif
#ifdef CHTHOLLY_RENDER_API_DX12

#endif

keg::GraphicsContext* keg::GraphicsContext::Create(void* window)
{
	switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: return new MetalContext(window);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: return nullptr;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: return new VulkanContext(window);
#endif
		default: assert(false); return nullptr;
	}
}

void keg::GraphicsContext::Init()
{
	switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: MetalContext::MetalInit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: break;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: VulkanContext::VulkanInit(); break;
#endif
		default: assert(false); break;
	}
}

void keg::GraphicsContext::Quit()
{
	switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: MetalContext::MetalQuit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: break;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: VulkanContext::VulkanQuit(); break;
#endif
		default: assert(false); break;
	}
}
