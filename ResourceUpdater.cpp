#include "pch.h"
#include "ResourceUpdater.h"
#include "HeapLayoutGenerator.h"

using namespace std;
using namespace winrt;
using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  ResourceUpdater::ResourceUpdater(const winrt::com_ptr<ID3D12CommandQueue>& copyQueue) :
    _copyQueue(copyQueue)
  { 
    _device = device_of(copyQueue);
  }

  void ResourceUpdater::ScheduleUpdate(ResourceHeapItem * heapItem, const GraphicsData* data)
  {
    _updates.push_back({ heapItem, data });
  }

  void ResourceUpdater::ExecuteUpdates()
  {
    if (_updates.empty()) return;

    //Build layout
    HeapLayoutGenerator layoutGenerator;
    auto resourceCategory = ResourceCategory::None;
    for (auto& update : _updates)
    {
      auto desc = update.HeapItem->Resource()->GetDesc();
      set_flag(resourceCategory, ToResourceCategory(update.HeapItem->Type()), true);
      layoutGenerator.AddItem(&update, desc);
    }
    auto layout = layoutGenerator.GetLayout(_device);

    //Generate heap desc
    D3D12_HEAP_DESC heapDesc;
    zero_memory(heapDesc);
    heapDesc.Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapDesc.Alignment = layout.Alignment;
    heapDesc.SizeInBytes = layout.Size;
    heapDesc.Flags = ToHeapFlags(resourceCategory);
    
    //Create new heap if needed
    if(!_stagingHeap || !AreCompatible(heapDesc, _stagingHeap->GetDesc()))
    {  
      check_hresult(_device->CreateHeap(&heapDesc, guid_of<ID3D12HeapT>(), _stagingHeap.put_void()));
    }

    //Prepare command list
    com_ptr<ID3D12CommandAllocator> commandAllocator;
    check_hresult(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COPY, guid_of<ID3D12CommandAllocator>(), commandAllocator.put_void()));

    com_ptr<ID3D12GraphicsCommandList> commandList;
    check_hresult(_device->CreateCommandList(
      0,
      D3D12_COMMAND_LIST_TYPE_COPY,
      commandAllocator.get(),
      nullptr,
      guid_of<ID3D12GraphicsCommandList>(),
      commandList.put_void()));

    //Prepare finish signal
    handle event{ CreateEvent(nullptr, false, false, nullptr) };
    com_ptr<ID3D12Fence> fence;
    check_hresult(_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, guid_of<ID3D12Fence>(), fence.put_void()));
    
    auto completedValue = fence->GetCompletedValue() + 1;
    check_hresult(fence->SetEventOnCompletion(completedValue, event.get()));

    //Create staging resources
    vector<com_ptr<ID3D12Resource>> resources;
    for (auto& layoutItem : layout.Items)
    {
      auto update = static_cast<ResourceUpdate*>(layoutItem.Tag);

      //Create CPU resource
      com_ptr<ID3D12Resource> stagingResource;
      check_hresult(_device->CreatePlacedResource(
        _stagingHeap.get(),
        layoutItem.Offset,
        &layoutItem.Desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        guid_of<ID3D12Resource>(),
        stagingResource.put_void()));

      //Copy data to staging area
      D3D12_RANGE range;
      zero_memory(range);

      void* target = nullptr;
      check_hresult(stagingResource->Map(0, &range, &target));
      memcpy(target, update->Data->Data(), update->Data->Length());
      range.End = update->Data->Length();
      stagingResource->Unmap(0, &range);

      //Copy staged data to GPU
      commandList->CopyResource(update->HeapItem->Resource().get(), stagingResource.get());

      //Keep resources alive
      resources.push_back(move(stagingResource));
    }
    commandList->Close();

    //Execute copy
    auto copyCommand = commandList.as<ID3D12CommandList>().get();
    _copyQueue->ExecuteCommandLists(1, &copyCommand);

    check_hresult(_copyQueue->Signal(fence.get(), completedValue));
    WaitForSingleObject(event.get(), INFINITE);

    //Cleanup
    _updates.clear();
  }
}