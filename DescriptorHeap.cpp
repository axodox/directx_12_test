#include "pch.h"
#include "DescriptorHeap.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;
using namespace std;
using namespace winrt;

namespace dx12test::Graphics
{
  bool DescriptorHeapItem::IsLoaded() const
  {
    return _isLoaded;
  }

  bool DescriptorHeapItem::TryLoad(const DescriptorHeapItemInitializationContext& context)
  {
    if (_isLoaded) return false;

    _isLoaded = OnTryLoad(context);
    return _isLoaded;
  }

  DescriptorHeap::DescriptorHeap(const winrt::com_ptr<ID3D12DeviceT>& device) :
    GraphicsResource(device)
  { }
  
  void DescriptorHeap::Rebuild()
  {
    lock_guard lock(_mutex);
    auto descriptors = CleanUpAndLockDescriptors();
    AllocateHeapSpace(descriptors);
    PopulateHeap(descriptors);
  }

  void DescriptorHeap::AddDescriptorHeapItem(const std::shared_ptr<DescriptorHeapItem>& heapItem)
  {
    lock_guard lock(_mutex);
    _items.push_back(heapItem);
  }

  std::vector<std::shared_ptr<DescriptorHeapItem>> DescriptorHeap::CleanUpAndLockDescriptors()
  {
    std::vector<std::shared_ptr<DescriptorHeapItem>> results;
    results.reserve(_items.size());

    auto it = _items.begin();
    while(it != _items.end())
    {
      auto item = it->lock();
      if (item)
      {
        results.push_back(move(item));
        it++;
      }
      else
      {
        swap(*it, _items.back());
        _items.pop_back();
      }
    }

    return results;
  }

  void DescriptorHeap::AllocateHeapSpace(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors)
  {
    //Calculate required heap size
    size_t newDescriptorCount = 0;
    for (auto& descriptor : descriptors)
    {
      if (!descriptor->IsLoaded())
      {
        newDescriptorCount++;
      }
    }

    auto requiredHeapSize = _heapStart + newDescriptorCount;

    //If size is large enough nothing to do
    if (_heapSize >= requiredHeapSize) return;

    //Unallocate old heap
    _heap = nullptr;

    //Calculate new size    
    requiredHeapSize = descriptors.size();
    auto newHeapSize = 1;
    do
    {
      newHeapSize *= 2;
    } while (newHeapSize < requiredHeapSize);

    //Build heap description
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    zero_memory(desc);
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE(Type());
    desc.NumDescriptors = newHeapSize;
    
    switch (Type())
    {
    case DescriptorHeapType::Resource:
    case DescriptorHeapType::Sampler:
      desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
      break;
    default:
      desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
      break;
    }

    //Create descriptor heap
    check_hresult(_device->CreateDescriptorHeap(
      &desc, 
      guid_of<ID3D12DescriptorHeap>(),
      _heap.put_void()));
    _heapSize = newHeapSize;
    _heapStart = 0;
  }
  
  void DescriptorHeap::PopulateHeap(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors)
  {
    //Determine upload location
    auto handleStartCpu = _heap->GetCPUDescriptorHandleForHeapStart();
    auto handleIncrement = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE(Type()));
    handleStartCpu.ptr += _heapStart * handleIncrement;

    //Initialize context
    DescriptorHeapItemInitializationContext context;
    zero_memory(context);
    context.Device = _device.get();
    context.CpuDescriptorHandle = handleStartCpu;
    context.Slot = _heapStart;

    //Load descriptors
    for (auto& descriptor : descriptors)
    {
      if (descriptor->TryLoad(context))
      {
        context.CpuDescriptorHandle.ptr += handleIncrement;
        context.Slot++;
      }
    }
        
    //Set new heap start
    _heapStart = context.Slot;
  }
}