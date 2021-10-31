#include "pch.h"
#include "ResourceHeapBuilder.h"
#include "ResourceHeapLayoutGenerator.h"
#include "ResourceUpdater.h"

using namespace winrt;
using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  ResourceHeapBuilder::ResourceHeapData& ResourceHeapBuilder::NewComponent()
  {
    _components.push_back(ResourceHeapData{});
    return _components.back();
  }

  ResourceHeapBuilder::ResourceHeapBuilder(ResourceCategory contentKind, const winrt::com_ptr<ID3D12CommandQueue>& copyQueue) :
    _heapKind(contentKind),
    _copyQueue(copyQueue)
  {
    _device = device_of(copyQueue);
  }

  ResourceCategory ResourceHeapBuilder::Kind() const
  {
    return _heapKind;
  }

  winrt::com_ptr<ID3D12HeapT> ResourceHeapBuilder::Build()
  {
    //Calculate layout for all resources
    ResourceHeapLayoutGenerator layoutGenerator;        
    for (auto& component : _components)
    {
      layoutGenerator.AddItem(&component, component.SourceData->GetDesc());
    }
    auto layout = layoutGenerator.GetLayout(_device);

    //Create resourceHeap for data storage
    D3D12_HEAP_DESC heapDesc;
    zero_memory(heapDesc);
    heapDesc.Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heapDesc.Alignment = layout.Alignment;
    heapDesc.SizeInBytes = layout.Size;
    heapDesc.Flags = ToHeapFlags(_heapKind);

    com_ptr<ID3D12HeapT> resourceHeap;
    check_hresult(_device->CreateHeap(&heapDesc, guid_of<ID3D12HeapT>(), resourceHeap.put_void()));

    //Allocate resources
    ResourceUpdater resourceUpdater{_copyQueue};
    for (auto& layoutItem : layout.Items)
    {
      auto heapData = static_cast<ResourceHeapData*>(layoutItem.Tag);

      com_ptr<ID3D12Resource> resource;
      check_hresult(_device->CreatePlacedResource(
        resourceHeap.get(),
        layoutItem.Offset,
        &layoutItem.Desc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        guid_of<ID3D12Resource>(),
        resource.put_void()));

      heapData->HeapItem->Initialize(resource);

      if (heapData->SourceData->Data())
      {
        resourceUpdater.ScheduleUpdate(heapData->HeapItem, heapData->SourceData);
      }
    }

    //Set initial values
    resourceUpdater.ExecuteUpdates();

    _components.clear();
    return resourceHeap;
  }
}