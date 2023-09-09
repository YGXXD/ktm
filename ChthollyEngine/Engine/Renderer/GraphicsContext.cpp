#include "GraphicsContext.h"

#if defined(CHTHOLLY_RENDER_API_METAL)
	#include "Metal/MetalGraphicsContext.h"
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif

ktl::GraphicsContext* ktl::GraphicsContext::Create(void* window)
{
#if defined(CHTHOLLY_RENDER_API_METAL)
    return new MetalGraphicsContext(window);
#elif defined(CHTHOLLY_RENDER_API_DX12)
	return nullptr;
#endif
}

void ktl::GraphicsContext::Init()
{
#if defined(CHTHOLLY_RENDER_API_METAL)
	MetalGraphicsContext::MetalInit();
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}

void ktl::GraphicsContext::Quit()
{
#if defined(CHTHOLLY_RENDER_API_METAL)
	MetalGraphicsContext::MetalQuit();
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}
