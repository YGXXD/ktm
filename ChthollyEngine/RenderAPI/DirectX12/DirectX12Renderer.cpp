#include "DirectX12Renderer.h"
#include "DirectX12Context.h"
#include <windows.h>

keg::DirectX12Renderer::DirectX12Renderer(void *window)
{
    CreateSwapChain(window);
    CreateRenderTargetView();
    DirectX12Context::GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(renderFence.GetAddressOf()));
}

keg::DirectX12Renderer::~DirectX12Renderer()
{
    renderFence.Reset();
    renderTargetViews.Reset();
    renderTargetImages.clear();
    swapChain.Reset();
}

void keg::DirectX12Renderer::SwapBuffer()
{
    static uint32_t currIndex = 0xffffffff;
    currIndex = ++currIndex % 2;

    ID3D12Device* device = DirectX12Context::GetDevice();
    ID3D12CommandAllocator* cmdAllocator = DirectX12Context::GetCmdAllocator();
    ID3D12CommandQueue* cmdQueue = DirectX12Context::GetCmdQueue();

    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList4> cmdList = nullptr;
    device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, nullptr, IID_PPV_ARGS(cmdList.GetAddressOf()));
    assert(cmdList.Get());

    const float clearValue[4] = { 0.5f, 1.f, 0.3f, 1.f };
    auto renderTargetHandle = renderTargetViews->GetCPUDescriptorHandleForHeapStart();
    renderTargetHandle.ptr += currIndex * DirectX12Context::GetRTVDescriptorSize();

    D3D12_RENDER_PASS_RENDER_TARGET_DESC renderTargetPassDesc = { };
    renderTargetPassDesc.BeginningAccess.Type = D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.Color[0] = 0.5f;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.Color[1] = 1.f;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.Color[2] = 0.3f;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.Color[3] = 1.f;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.DepthStencil.Depth = 0.f;
    renderTargetPassDesc.BeginningAccess.Clear.ClearValue.DepthStencil.Stencil = 0.f;
    renderTargetPassDesc.cpuDescriptor = renderTargetHandle;
    renderTargetPassDesc.EndingAccess.Type = D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE;
    cmdList->BeginRenderPass(1, &renderTargetPassDesc, nullptr, D3D12_RENDER_PASS_FLAG_NONE);

    cmdList->EndRenderPass();

    cmdList->Close();
    ID3D12CommandList* lists[1] = { cmdList.Get() };
    cmdQueue->ExecuteCommandLists(1, lists);
    
    static uint64_t fenceCount = 0;
    cmdQueue->Signal(renderFence.Get(), ++fenceCount);

    swapChain->Present(0, 0);
}

void keg::DirectX12Renderer::CreateSwapChain(void *window)
{
    swapChainCount = 2;
    HWND hWnd = (HWND)window;
	RECT windowRect;
	GetClientRect(hWnd, &windowRect);

    DXGI_SWAP_CHAIN_DESC swapChainCreateInfo = { };
    swapChainCreateInfo.BufferDesc.Width = windowRect.right - windowRect.left;
    swapChainCreateInfo.BufferDesc.Height = windowRect.bottom - windowRect.top;
    swapChainCreateInfo.BufferDesc.RefreshRate.Numerator = 60;
    swapChainCreateInfo.BufferDesc.RefreshRate.Denominator = 1;
    swapChainCreateInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainCreateInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainCreateInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainCreateInfo.SampleDesc.Count = 1;
    swapChainCreateInfo.SampleDesc.Quality = 0;
    swapChainCreateInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainCreateInfo.BufferCount = swapChainCount;
    swapChainCreateInfo.OutputWindow = hWnd;
    swapChainCreateInfo.Windowed = true;
    swapChainCreateInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; //此标志不能与多重采样和部分表示一起使用。
    swapChainCreateInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 设置此标志以使应用程序能够通过调用来切换交换链大小

    DirectX12Context::GetDXGIFactory()->CreateSwapChain(DirectX12Context::GetCmdQueue(), &swapChainCreateInfo, swapChain.GetAddressOf());
    assert(swapChain.Get());

    renderTargetImages.resize(swapChainCount);
    for(int i = 0; i < renderTargetImages.size(); ++i)
    {
        swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargetImages[i].GetAddressOf()));
    }
}

void keg::DirectX12Renderer::CreateRenderTargetView()
{
    D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewsDesc = { };
    renderTargetViewsDesc.NodeMask = 0;
    renderTargetViewsDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    renderTargetViewsDesc.NumDescriptors = swapChainCount;
    renderTargetViewsDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    DirectX12Context::GetDevice()->CreateDescriptorHeap(&renderTargetViewsDesc, IID_PPV_ARGS(renderTargetViews.GetAddressOf()));
    assert(renderTargetViews.Get());

    UINT rtvSize = DirectX12Context::GetRTVDescriptorSize();
    D3D12_CPU_DESCRIPTOR_HANDLE descHeapHandle = renderTargetViews->GetCPUDescriptorHandleForHeapStart();
    for(int i = 0; i < swapChainCount; ++i)
    {
        D3D12_RENDER_TARGET_VIEW_DESC renderTargerViewDesc;
        DirectX12Context::GetDevice()->CreateRenderTargetView(renderTargetImages[i].Get(), nullptr, descHeapHandle);
        descHeapHandle.ptr += rtvSize;
    }
}
