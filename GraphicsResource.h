#pragma once
#include "GraphicsDefines.h"

namespace dx12test::Graphics
{
  class GraphicsResource
  {
  public:
    const winrt::com_ptr<ID3D12DeviceT>& Device() const;

  protected:
    winrt::com_ptr<ID3D12DeviceT> _device;
  };
}