#ifndef _DIRECTX12_CONTEXT_H_
#define _DIRECTX12_CONTEXT_H_

#include "Render/GraphicsContext.h"
#include <d3d12.h>

namespace keg
{
class DirectX12Context final
{
public:
    static void DirectX12Init();
    static void DirectX12Quit();
};
}

#endif