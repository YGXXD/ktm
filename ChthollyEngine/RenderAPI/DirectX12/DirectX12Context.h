#ifndef _DIRECTX12_CONTEXT_H_
#define _DIRECTX12_CONTEXT_H_

#include "Render/GraphicsContext.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace keg
{
class DirectX12Context final
{
public:
    static void DirectX12Init();
    static void DirectX12Quit();

    static CHTHOLLY_INLINE IDXGIFactory4* GetDXGIFactory() { return dxgiFactory.Get(); }
    static CHTHOLLY_INLINE ID3D12Device* GetDevice() { return device.Get(); };
    static CHTHOLLY_INLINE ID3D12CommandQueue* GetCmdQueue() { return cmdQueue.Get(); }
    static CHTHOLLY_INLINE ID3D12CommandAllocator* GetCmdAllocator() { return cmdAllocator.Get(); }
    static CHTHOLLY_INLINE uint32_t GetRTVDescriptorSize() { return rtvDescriptorSize; }
    static CHTHOLLY_INLINE uint32_t GetDSVDescriptorSize() { return dsvDescriptorSize; }

private:
    static Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory;
    static Microsoft::WRL::ComPtr<ID3D12Device> device;
    static Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
    static Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
    static uint32_t rtvDescriptorSize;
    static uint32_t dsvDescriptorSize;
};
}

#endif