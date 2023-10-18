#include "Renderer.h"
#include "GraphicsContext.h"

#ifdef CHTHOLLY_RENDER_API_METAL
	#include "Metal/MetalRenderer.h"
#endif
#ifdef CHTHOLLY_RENDER_API_VULKAN
	#include "Vulkan/VulkanRenderer.h"
#endif
#ifdef CHTHOLLY_RENDER_API_DX12
	#include "DirectX12/DirectX12Renderer.h"
#endif

keg::Renderer* keg::Renderer::Create(void* window)
{
	switch(GraphicsContext::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case GraphicsAPI::Metal: return new MetalRenderer(window);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case GraphicsAPI::DX12: return new DirectX12Renderer(window);
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case GraphicsAPI::Vulkan: return new VulkanRenderer(window);
#endif
		default: assert(false); return nullptr;
	}
}