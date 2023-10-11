#include "Buffer.h"
#include "Renderer.h"

#ifdef CHTHOLLY_RENDER_API_METAL
	#include "Metal/MetalBuffer.h"
#endif
#ifdef CHTHOLLY_RENDER_API_VULKAN
	#include "Vulkan/VulkanBuffer.h"
#endif
#ifdef CHTHOLLY_RENDER_API_DX12

#endif

keg::VertexBuffer* keg::VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: return new MetalVertexBuffer(vertices, size);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: return nullptr;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: return new VulkanVertexBuffer(vertices, size);
#endif
		default: assert(false); return nullptr;
	}
}

keg::IndexBuffer* keg::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch(Renderer::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case RenderAPI::Metal: return new MetalIndexBuffer(indices, count);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case RenderAPI::DX12: return nullptr;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case RenderAPI::Vulkan: return new VulkanIndexBuffer(indices, count);
#endif
		default: assert(false); return nullptr;
	}
}