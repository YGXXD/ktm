#include "DirectX12Context.h"

Microsoft::WRL::ComPtr<IDXGIFactory4> keg::DirectX12Context::dxgiFactory;
Microsoft::WRL::ComPtr<ID3D12Device> keg::DirectX12Context::device;
Microsoft::WRL::ComPtr<ID3D12CommandQueue> keg::DirectX12Context::cmdQueue;
Microsoft::WRL::ComPtr<ID3D12CommandAllocator> keg::DirectX12Context::cmdAllocator;
UINT keg::DirectX12Context::rtvDescriptorSize;
UINT keg::DirectX12Context::dsvDescriptorSize;

void keg::DirectX12Context::DirectX12Init()
{
    Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
    D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
    debugController->EnableDebugLayer();

    CreateDXGIFactory(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));
    // 创建设备
    D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(device.GetAddressOf()));
    if(!device.Get())
    {
        Microsoft::WRL::ComPtr<IDXGIAdapter> pWarpAdapter;
        dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(pWarpAdapter.GetAddressOf()));
        D3D12CreateDevice(pWarpAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(device.GetAddressOf()));
    }
    assert(device.Get());

    // 创建命令队列
    D3D12_COMMAND_QUEUE_DESC queueDesc;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;
    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(cmdQueue.GetAddressOf()));
    assert(cmdQueue.Get());
    device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator.GetAddressOf()));
    assert(cmdAllocator.Get());

    rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    dsvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

void keg::DirectX12Context::DirectX12Quit()
{
    cmdAllocator.Reset();
    cmdQueue.Reset();
    device.Reset();
    dxgiFactory.Reset();
}