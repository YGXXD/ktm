#include "Buffer.h"

#if defined(CHTHOLLY_RENDER_API_METAL)
    
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif

ktl::VertexBuffer* ktl::VertexBuffer::Create(float* vertices, uint32_t size)
{
    return nullptr;
}

ktl::IndexBuffer* ktl::IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    return nullptr;
}