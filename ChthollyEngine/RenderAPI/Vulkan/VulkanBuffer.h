#ifndef _VULKAN_BUFFER_H_
#define _VULKAN_BUFFER_H_

#include "Render/Buffer.h"
#include <vulkan/vulkan.h>

namespace keg
{
class VulkanVertexBuffer : public VertexBuffer
{
public:
    VulkanVertexBuffer(float* vertices, uint32_t size);
    virtual ~VulkanVertexBuffer();

    virtual void Bind() override;
    virtual void UnBind() override;

    CHTHOLLY_INLINE VkBuffer GetBuffer() const { return vBuffer; }
private:
    VkBuffer vBuffer;
};

class VulkanIndexBuffer : public IndexBuffer
{
public:
    VulkanIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~VulkanIndexBuffer();

    virtual void Bind() override;
    virtual void UnBind() override;
    CHTHOLLY_INLINE VkBuffer GetBuffer() const { return iBuffer; }
private:
    VkBuffer iBuffer;
};
}

#endif