#include "pch.h"
#include "GraphicsDevice.h"

using namespace winrt;

namespace dx12test::Graphics
{
  GraphicsDevice::GraphicsDevice()
  {
#ifndef NDEBUG
    com_ptr<ID3D12Debug> debug;
    check_hresult(D3D12GetDebugInterface(guid_of<ID3D12Debug>(), debug.put_void()));
    debug->EnableDebugLayer();
#endif // !NDEBUG

    check_hresult(D3D12CreateDevice(
      nullptr, 
      D3D_REQUIRED_FEATURE_LEVEL, 
      guid_of<ID3D12DeviceT>(), 
      _device.put_void()));

    D3D12_COMMAND_QUEUE_DESC queueDesc{};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    check_hresult(_device->CreateCommandQueue(&queueDesc, guid_of<ID3D12CommandQueue>(), _directQueue.put_void()));
  }

  const com_ptr<ID3D12CommandQueue>& GraphicsDevice::DirectQueue() const
  {
    return _directQueue;
  }
}