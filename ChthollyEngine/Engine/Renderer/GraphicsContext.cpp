#include "GraphicsContext.h"

#if defined(CHTHOLLY_RENDER_API_METAL)

#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif

xxd::GraphicsContext* xxd::GraphicsContext::Create(void* window)
{
#if defined(CHTHOLLY_RENDER_API_METAL)
    return nullptr;
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}

void xxd::GraphicsContext::Init()
{
#if defined(CHTHOLLY_RENDER_API_METAL)
    
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}

void xxd::GraphicsContext::Quit()
{
#if defined(CHTHOLLY_RENDER_API_METAL)
   
#elif defined(CHTHOLLY_RENDER_API_DX12)

#endif
}