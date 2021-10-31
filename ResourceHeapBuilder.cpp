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

  winrt::com_ptr<ID3D12HeapT> ResourceHeapBuilder::Build()
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
    uint64_t stagingSize = 0;
    uint64_t offset = 0;
    for (auto& component : _components)
    {
      auto desc = component.SourceData->GetDesc();
      auto allocationInfo = _device->GetResourceAllocationInfo(0, 1, &desc);

      auto shift = offset % allocationInfo.Alignment;
      offset += shift == 0 ? 0 : allocationInfo.Alignment - shift;

      layouts.push_back({ &component, desc, offset });
      offset += allocationInfo.SizeInBytes;

      if (component.SourceData->Data() && allocationInfo.SizeInBytes > stagingSize)
      {
        stagingSize = allocationInfo.SizeInBytes;
      }
    }

    //Create resourceHeap for data storage
    D3D12_HEAP_DESC heapDesc;
    zero_memory(heapDesc);
    heapDesc.Properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heapDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;

    auto shift = offset % heapDesc.Alignment;
    offset += shift == 0 ? 0 : heapDesc.Alignment - shift;
    heapDesc.SizeInBytes = offset;

    if (!has_flag(_heapKind, HeapContentKind::Buffers))
    {
      heapDesc.Flags |= D3D12_HEAP_FLAG_DENY_BUFFERS;
    }

    if (!has_flag(_heapKind, HeapContentKind::Textures))
    {
      heapDesc.Flags |= D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES;
    }

    if (!has_flag(_heapKind, HeapContentKind::RenderTargets))
    {
      heapDesc.Flags |= D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES;
    }
    
    com_ptr<ID3D12HeapT> resourceHeap;
    check_hresult(_device->CreateHeap(&heapDesc, guid_of<ID3D12HeapT>(), resourceHeap.put_void()));

    //Allocate resources
    for (auto& layout : layouts)
    {
      com_ptr<ID3D12Resource> resource;
      check_hresult(_device->CreatePlacedResource(
        resourceHeap.get(),
        layout.Offset,
        &layout.Desc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        guid_of<ID3D12Resource>(),
        resource.put_void()));

      layout.Component->HeapItem->Initialize(resource);
    }

    //Create staging heap, if we need to upload data
    if (stagingSize > 0)
    {
      heapDesc.Properties.Type = D3D12_HEAP_TYPE_UPLOAD;

      shift = stagingSize % heapDesc.Alignment;
      stagingSize += shift == 0 ? 0 : heapDesc.Alignment - shift;
      heapDesc.SizeInBytes = stagingSize;

      com_ptr<ID3D12HeapT> stagingHeap;
      check_hresult(_device->CreateHeap(&heapDesc, guid_of<ID3D12HeapT>(), stagingHeap.put_void()));

      //Upload data to GPU
      com_ptr<ID3D12CommandAllocator> commandAllocator;
      check_hresult(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COPY, guid_of<ID3D12CommandAllocator>(), commandAllocator.put_void()));

      handle event{ CreateEvent(nullptr, false, false, nullptr) };
      com_ptr<ID3D12Fence> fence;
      check_hresult(_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, guid_of<ID3D12Fence>(), fence.put_void()));

      for (auto& layout : layouts)
      {
        auto sourceData = layout.Component->SourceData;
        if (sourceData->Data() == nullptr) continue;

        //Create CPU resource
        com_ptr<ID3D12Resource> stagingResource;
        check_hresult(_device->CreatePlacedResource(
          stagingHeap.get(),
          0,
          &layout.Desc,
          D3D12_RESOURCE_STATE_GENERIC_READ,
          nullptr,
          guid_of<ID3D12Resource>(),
          stagingResource.put_void()));

        //Copy data to staging area
        D3D12_RANGE range;
        zero_memory(range);

        void* target = nullptr;
        check_hresult(stagingResource->Map(0, &range, &target));
        memcpy(target, sourceData->Data(), sourceData->Length());
        range.End = sourceData->Length();
        stagingResource->Unmap(0, &range);

        //Copy staged data to GPU
        com_ptr<ID3D12GraphicsCommandList> commandList;
        check_hresult(_device->CreateCommandList(
          0,
          D3D12_COMMAND_LIST_TYPE_COPY,
          commandAllocator.get(),
          nullptr,
          guid_of<ID3D12GraphicsCommandList>(),
          commandList.put_void()));

        commandList->CopyResource(layout.Component->HeapItem->Resource().get(), stagingResource.get());
        commandList->Close();

        auto copyCommand = commandList.as<ID3D12CommandList>().get();
        _copyQueue->ExecuteCommandLists(1, &copyCommand);

        auto completedValue = fence->GetCompletedValue() + 1;
        check_hresult(fence->SetEventOnCompletion(completedValue, event.get()));
        check_hresult(_copyQueue->Signal(fence.get(), completedValue));
        WaitForSingleObject(event.get(), INFINITE);

        check_hresult(commandList->Reset(commandAllocator.get(), nullptr));
      }
    }

    return resourceHeap;
  }
}