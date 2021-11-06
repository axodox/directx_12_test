#pragma once
#include "GraphicsDefines.h"

namespace dx12test::Graphics
{
  class GraphicsResource
  {
  public:
    GraphicsResource() = default;
    GraphicsResource(const winrt::com_ptr<ID3D12DeviceT>& device);
    virtual ~GraphicsResource() = default;

    const winrt::com_ptr<ID3D12DeviceT>& Device() const;

  protected:
    winrt::com_ptr<ID3D12DeviceT> _device;
  };
}