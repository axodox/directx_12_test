#include "pch.h"
#include "GraphicsResource.h"

namespace dx12test::Graphics
{
  const winrt::com_ptr<ID3D12DeviceT>& GraphicsResource::Device() const
  {
    return _device;
  }
}