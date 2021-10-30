#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  typedef ID3D12Device ID3D12DeviceT;
  typedef IDXGIFactory4 IDXGIFactoryT;
  typedef ID3D12Heap ID3D12HeapT;

  const D3D_FEATURE_LEVEL D3D_REQUIRED_FEATURE_LEVEL = D3D_FEATURE_LEVEL_12_1;

  template <typename T>
  winrt::com_ptr<ID3D12DeviceT> device_of(const T& child)
  {
    winrt::com_ptr<ID3D12DeviceT> device;
    winrt::check_hresult(child->GetDevice(guid_of<ID3D12DeviceT>(), device.put_void()));
    return device;
  }
}