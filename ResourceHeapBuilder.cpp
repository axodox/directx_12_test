#include "pch.h"
#include "ResourceHeapBuilder.h"
#include "BitwiseOperations.h"

using namespace winrt;
using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  ResourceHeapBuilder::ResourceHeapData& ResourceHeapBuilder::NewComponent()
  {
    _components.push_back(ResourceHeapData{});
    return _components.back();
  }

  ResourceHeapBuilder::ResourceHeapBuilder(HeapContentKind contentKind, const winrt::com_ptr<ID3D12CommandQueue>& copyQueue) :
    _heapKind(contentKind),
    _copyQueue(copyQueue)
  {
    _device = device_of(copyQueue);
  }

  HeapContentKind ResourceHeapBuilder::Kind() const
  {
    return _heapKind;
  }

  void ResourceHeapBuilder::Build()
  {
    //Calculate layout for all resources
    struct ResourceLayout
    {
      ResourceHeapData* Component;
      D3D12_RESOURCE_DESC Desc;
      uint64_t Offset;
    };
    
    std::vector<ResourceLayout> layouts;
    layouts.reserve(_components.size());
    uint64_t offset = 0;
    for (auto& component : _components)
    {
      auto desc = component.SourceData->GetDesc();

      auto allocationInfo = _device->GetResourceAllocationInfo(0, 1, &desc);

      auto shift = offset % allocationInfo.Alignment;
      offset += shift == 0 ? 0 : allocationInfo.Alignment - shift;

      layouts.push_back({ &component, desc, offset });

      offset += allocationInfo.SizeInBytes;
    }

    //Create heap for data storage
    D3D12_HEAP_DESC heapDesc;
    zero_memory(heapDesc);
    heapDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;

    auto shift = offset % heapDesc.Alignment;
    offset += shift == 0 ? 0 : heapDesc.Alignment - shift;
    heapDesc.SizeInBytes = offset;

    if (!has_flag(_heapKind, HeapContentKind::Buffers))
    {
      heapDesc.Flags = D3D12_HEAP_FLAG_DENY_BUFFERS;
    }

    if (!has_flag(_heapKind, HeapContentKind::Textures))
    {
      heapDesc.Flags = D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES;
    }

    if (!has_flag(_heapKind, HeapContentKind::RenderTargets))
    {
      heapDesc.Flags = D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES;
    }
    
    com_ptr<ID3D12HeapT> heap;
    check_hresult(_device->CreateHeap(&heapDesc, guid_of<ID3D12HeapT>(), heap.put_void()));

    //Allocate resources
    for (auto& layout : layouts)
    {
      com_ptr<ID3D12Resource> resource;
      check_hresult(_device->CreatePlacedResource(
        heap.get(),
        layout.Offset,
        &layout.Desc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        guid_of<ID3D12Resource>(),
        resource.put_void()));

      layout.Component->HeapItem->Initialize(resource);
    }
  }
}