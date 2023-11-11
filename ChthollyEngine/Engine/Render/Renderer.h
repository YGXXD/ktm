#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Basic/Basic.h"

namespace keg
{
class CHTHOLLY_ENGINE_API Renderer
{
public:
    static Renderer* Create(void* window);
    virtual ~Renderer() = default;
	virtual void SwapBuffer() = 0;
};
}

#endif