#include "pch.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  const winrt::com_ptr<ID3D12Resource>& ResourceHeapItem::Resource() const
  {
    return _resource;
  }

  void ResourceHeapItem::Initialize(const winrt::com_ptr<ID3D12Resource>& resource)
  {
    _resource = resource;
    OnInitialize();
  }
}