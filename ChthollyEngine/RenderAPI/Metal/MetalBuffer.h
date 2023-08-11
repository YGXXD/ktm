#ifndef _METAL_BUFFER_H_
#define _METAL_BUFFER_H_

#include "Renderer/Buffer.h"

namespace xxd 
{
class MetalVertexBuffer : public VertexBuffer
{
public:
    MetalVertexBuffer(float* vertices, uint32_t size);
    virtual ~MetalVertexBuffer();

    virtual void Bind() override;
    virtual void UnBind() override;
};

class MetalIndexBuffer : public IndexBuffer
{
public:
    MetalIndexBuffer(uint32_t* indices, uint32_t size);
    virtual ~MetalIndexBuffer();

    virtual void Bind() override;
    virtual void UnBind() override;
};
}

#endif