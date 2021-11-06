#include "pch.h"
#include "GraphicsResource.h"

namespace dx12test::Graphics
{
    GraphicsResource::GraphicsResource(const winrt::com_ptr<ID3D12DeviceT>& device) :
      _device(device)
    { }

    const winrt::com_ptr<ID3D12DeviceT>& GraphicsResource::Device() const
  {
    return _device;
  }
}