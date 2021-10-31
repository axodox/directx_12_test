#include "pch.h"
#include "HeapLayoutGenerator.h"

using namespace std;

namespace dx12test::Graphics
{
  void HeapLayoutGenerator::AddItem(void* tag, const D3D12_RESOURCE_DESC& desc)
  {
    _items.push_back({ tag, desc });
  }
  
  HeapLayout HeapLayoutGenerator::GetLayout(const winrt::com_ptr<ID3D12DeviceT>& device, uint64_t alignment)
  {
    HeapLayout layout;
    layout.Items.reserve(_items.size());
    uint64_t offset = 0;
    for (auto& item : _items)
    {
      auto allocationInfo = device->GetResourceAllocationInfo(0, 1, &item.Desc);

      auto shift = offset % allocationInfo.Alignment;
      offset += shift == 0 ? 0 : allocationInfo.Alignment - shift;

      item.Offset = offset;
      layout.Items.push_back(item);
      offset += allocationInfo.SizeInBytes;
    }

    auto shift = offset % alignment;
    offset += shift == 0 ? 0 : alignment - shift;
    layout.Size = offset;
    layout.Alignment = alignment;
    return layout;
  }
}