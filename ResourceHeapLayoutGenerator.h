#pragma once
#include "GraphicsDefines.h"

namespace dx12test::Graphics
{
  struct ResourceHeapLayoutItem
  {
    void* Tag;
    D3D12_RESOURCE_DESC Desc;
    uint64_t Offset;
  };

  struct ResourceHeapLayout
  {
    std::vector<ResourceHeapLayoutItem> Items;
    uint64_t Size;
    uint64_t Alignment;
  };

  class ResourceHeapLayoutGenerator
  {
  public:
    void AddItem(void* tag, const D3D12_RESOURCE_DESC& desc);

    ResourceHeapLayout GetLayout(const winrt::com_ptr<ID3D12DeviceT>& device, uint64_t alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT);

  private:
    std::list<ResourceHeapLayoutItem> _items;
  };
}