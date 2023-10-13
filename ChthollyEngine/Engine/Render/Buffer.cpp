#include "Buffer.h"
#include "GraphicsContext.h"

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
    switch(GraphicsContext::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case GraphicsAPI::Metal: return new MetalVertexBuffer(vertices, size);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case GraphicsAPI::DX12: return nullptr;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case GraphicsAPI::Vulkan: return new VulkanVertexBuffer(vertices, size);
#endif
		default: assert(false); return nullptr;
	}
}

keg::IndexBuffer* keg::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch(GraphicsContext::GetAPI()) 
	{
#ifdef	CHTHOLLY_RENDER_API_METAL
		case GraphicsAPI::Metal: return new MetalIndexBuffer(indices, count);
#endif
#ifdef	CHTHOLLY_RENDER_API_DX12 
		case GraphicsAPI::DX12: return nullptr;
#endif
#ifdef	CHTHOLLY_RENDER_API_VULKAN
		case GraphicsAPI::Vulkan: return new VulkanIndexBuffer(indices, count);
#endif
		default: assert(false); return nullptr;
	}
}