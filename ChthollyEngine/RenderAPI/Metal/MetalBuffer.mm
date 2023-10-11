#include "MetalBuffer.h"
#include "MetalGraphicsContext.h"

keg::MetalVertexBuffer::MetalVertexBuffer(float* vertices, uint32_t size)
{
    @autoreleasepool
    {
        id<MTLDevice> device = MetalGraphicsContext::GetDevice();
        vBuffer = [device newBufferWithLength:size options:MTLResourceStorageModeShared];
        memcpy(vBuffer.contents, vertices, size);
    }
}

keg::MetalVertexBuffer::~MetalVertexBuffer()
{
     [vBuffer release];
}

void keg::MetalVertexBuffer::Bind()
{
    
}

void keg::MetalVertexBuffer::UnBind()
{

}

keg::MetalIndexBuffer::MetalIndexBuffer(uint32_t* indices, uint32_t count)
{
    @autoreleasepool
    {
        indicesCount = count;
        const uint32_t size = indicesCount * sizeof(uint32_t);
        id<MTLDevice> device = MetalGraphicsContext::GetDevice();
        iBuffer = [device newBufferWithLength:size options:MTLResourceStorageModeShared];
        memcpy(iBuffer.contents, indices, size);
    }
}

keg::MetalIndexBuffer::~MetalIndexBuffer()
{
    [iBuffer release];
}

void keg::MetalIndexBuffer::Bind()
{

}

void keg::MetalIndexBuffer::UnBind()
{

}