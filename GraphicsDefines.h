#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  typedef ID3D12Device ID3D12DeviceT;
  typedef IDXGIFactory4 IDXGIFactoryT;
  typedef ID3D12Heap ID3D12HeapT;
  typedef ID3D12Resource ID3D12ResourceT;
  typedef ID3D12GraphicsCommandList6 ID3D12GraphicsCommandListT;

  const D3D_FEATURE_LEVEL D3D_REQUIRED_FEATURE_LEVEL = D3D_FEATURE_LEVEL_12_1;

  template <typename T>
  winrt::com_ptr<ID3D12DeviceT> device_of(const T& child)
  {
    winrt::com_ptr<ID3D12DeviceT> device;
    winrt::check_hresult(child->GetDevice(winrt::guid_of<ID3D12DeviceT>(), device.put_void()));
    return device;
  }
}