#include "Buffer.h"

#if defined(CHTHOLLY_RENDER_API_METAL)
    
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif

keg::VertexBuffer* keg::VertexBuffer::Create(float* vertices, uint32_t size)
{
    return nullptr;
}

keg::IndexBuffer* keg::IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    return nullptr;
}