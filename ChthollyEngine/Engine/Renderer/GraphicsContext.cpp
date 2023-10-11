#include "GraphicsContext.h"
#include "Renderer.h"

#ifdef CHTHOLLY_RENDER_API_METAL
	#include "Metal/MetalGraphicsContext.h"
#endif
#ifdef CHTHOLLY_RENDER_API_VULKAN
	#include "Vulkan/VulkanGraphicsContext.h"
#endif
#ifdef CHTHOLLY_RENDER_API_DX12

#endif

keg::GraphicsContext* keg::GraphicsContext::Create(void* window)
{
	switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: return new MetalGraphicsContext(window);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: return nullptr;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: return new VulkanGraphicsContext(window);
#endif
		default: assert(false); return nullptr;
	}
}

void keg::GraphicsContext::Init()
{
	switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: MetalGraphicsContext::MetalInit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: break;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: VulkanGraphicsContext::VulkanInit(); break;
#endif
		default: assert(false); break;
	}
}

void keg::GraphicsContext::Quit()
{
	switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: MetalGraphicsContext::MetalQuit(); break;
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: break;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: VulkanGraphicsContext::VulkanQuit(); break;
#endif
		default: assert(false); break;
	}
}
