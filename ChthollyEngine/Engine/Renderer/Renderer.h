#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Basic/SetupBase.h"

namespace keg
{
enum class RenderAPI
{
    None, Metal, DX12, Vulkan
};

class CHTHOLLY_ENGINE_API Renderer
{
public:
    static CHTHOLLY_INLINE RenderAPI GetAPI() { return sAPI; };
private:
    static RenderAPI sAPI;
};
}

#endif