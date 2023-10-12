#include "Renderer.h"

#if defined(CHTHOLLY_RENDER_API_METAL)
keg::RenderAPI keg::Renderer::sAPI = keg::RenderAPI::Metal;
#elif defined(CHTHOLLY_RENDER_API_DX12)
keg::RenderAPI keg::Renderer::sAPI = keg::RenderAPI::DX12;
#elif defined(CHTHOLLY_RENDER_API_VULKAN)
keg::RenderAPI keg::Renderer::sAPI = keg::RenderAPI::Vulkan;
#endif