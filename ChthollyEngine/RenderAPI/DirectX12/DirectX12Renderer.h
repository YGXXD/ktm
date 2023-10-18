#ifndef _DIRECTX12_RENDERER_H_
#define _DIRECTX12_RENDERER_H_

#include "Render/Renderer.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace keg
{
class DirectX12Renderer : public Renderer
{
public:
    DirectX12Renderer(void* window);
    ~DirectX12Renderer();

    virtual void SwapBuffer();
private:
    void CreateSwapChain(void* window);
    void CreateRenderTargetView();

    uint32_t swapChainCount;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

    std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> renderTargetImages;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> renderTargetViews;

    Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilImage;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> depthStencilView;

    Microsoft::WRL::ComPtr<ID3D12Fence> renderFence;
};
}

#endif