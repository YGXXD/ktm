#ifndef _METAL_BUFFER_H_
#define _METAL_BUFFER_H_

#include "Render/Buffer.h"
#import <Metal/Metal.h>

namespace keg 
{
class MetalVertexBuffer : public VertexBuffer
{
public:
    MetalVertexBuffer(float* vertices, uint32_t size);
    virtual ~MetalVertexBuffer();

    virtual void Bind() override;
    virtual void UnBind() override;

    CHTHOLLY_INLINE id<MTLBuffer> GetBuffer() const { return vBuffer; }
private:
    id<MTLBuffer> vBuffer;
};

class MetalIndexBuffer : public IndexBuffer
{
public:
    MetalIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~MetalIndexBuffer();

    virtual void Bind() override;
    virtual void UnBind() override;
    CHTHOLLY_INLINE id<MTLBuffer> GetBuffer() const { return iBuffer; }
private:
    id<MTLBuffer> iBuffer;
};
}

#endif