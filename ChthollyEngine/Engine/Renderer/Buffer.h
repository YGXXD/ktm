#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Util/Config.h"

namespace keg
{
class CHTHOLLY_ENGINE_API VertexBuffer
{
public:
    virtual ~VertexBuffer() { };
    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    static VertexBuffer* Create(float* vertices, uint32_t size);
};   

class CHTHOLLY_ENGINE_API IndexBuffer
{
public:
    virtual ~IndexBuffer() { };
    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};
}

#endif