#ifndef _GRAPHICS_CONTEXT_H_
#define _GRAPHICS_CONTEXT_H_

#include "Chtholly.h"

namespace xxd
{
class CHTHOLLY_API GraphicsContext
{
public:
    static GraphicsContext* Create(void* window);
    static void Init();
    static void Quit();

	virtual ~GraphicsContext() = default;
	virtual void SwapBuffer() = 0;
};
}

#endif
