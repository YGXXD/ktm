#include "GraphicsContext.h"

#if defined(CHTHOLLY_RENDER_API_METAL)
	#include "Metal/MetalGraphicsContext.h"
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif

xxd::GraphicsContext* xxd::GraphicsContext::Create(void* window)
{
#if defined(CHTHOLLY_RENDER_API_METAL)
    return new MetalGraphicsContext(window);
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}

void xxd::GraphicsContext::Init()
{
#if defined(CHTHOLLY_RENDER_API_METAL)
	MetalGraphicsContext::MetalInit();
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}

void xxd::GraphicsContext::Quit()
{
#if defined(CHTHOLLY_RENDER_API_METAL)
	MetalGraphicsContext::MetalQuit();
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}
