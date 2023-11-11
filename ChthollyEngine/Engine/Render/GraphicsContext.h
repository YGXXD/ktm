#ifndef _GRAPHICS_CONTEXT_H_
#define _GRAPHICS_CONTEXT_H_

#include "Basic/Basic.h"

namespace keg
{

enum class GraphicsAPI
{
    None, Metal, DX12, Vulkan
};

class CHTHOLLY_ENGINE_API GraphicsContext final
{
public:
    static void Init();
    static void Quit();

    static GraphicsAPI GetAPI() { return sAPI; }
private:
    static GraphicsAPI sAPI;
};
}

#endif
