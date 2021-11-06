#include "pch.h"
#include "DescriptorHeap.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;
using namespace std;
using namespace winrt;

namespace dx12test::Graphics
{
  DescriptorHeap::DescriptorHeap(const winrt::com_ptr<ID3D12DeviceT>& device) :
    _device(device)
  { }
  
  void DescriptorHeap::Rebuild()
  {
    lock_guard lock(_mutex);
    auto descriptors = CleanUpAndLockDescriptors();
    AllocateHeapSpace(descriptors);
    PopulateHeap(descriptors);
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

    //Unload all resources
    for (auto& descriptor : descriptors)
    {
      descriptor->Unload();
    }

    //Remove heaps
    _defaultHeap = nullptr;
    _uploadHeap = nullptr;

    //Calculate new size    
    requiredHeapSize = descriptors.size();
    auto newHeapSize = _heapSize;
    do
    {
      newHeapSize *= 2;
    } while (newHeapSize < requiredHeapSize);

    //Build heap description
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    zero_memory(desc);
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE(Type());
    desc.NumDescriptors = newHeapSize;
    
    bool requiresUploadHeap;
    switch (Type())
    {
    case DescriptorHeapType::Resource:
    case DescriptorHeapType::Sampler:
      desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
      requiresUploadHeap = true;
      break;
    default:
      desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
      requiresUploadHeap = false;
      break;
    }

    //Create descriptor heap
    check_hresult(_device->CreateDescriptorHeap(
      &desc, 
      guid_of<ID3D12DescriptorHeap>(),
      _defaultHeap.put_void()));
    _heapSize = newHeapSize;
    _heapStart = 0;

    //Create upload heap as needed
    if (requiresUploadHeap)
    {
      desc.Flags &= ~D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
      check_hresult(_device->CreateDescriptorHeap(
        &desc,
        guid_of<ID3D12DescriptorHeap>(),
        _uploadHeap.put_void()));
    }
  }
  
  void DescriptorHeap::PopulateHeap(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors)
  {
    //Use upload heap unless the default heap is CPU accessible
    auto uploadHeap = _uploadHeap ? _uploadHeap.get() : _defaultHeap.get();

    //Determine upload location
    auto handleSlot = uploadHeap->GetCPUDescriptorHandleForHeapStart();
    auto handleIncrement = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE(Type()));
    handleSlot.ptr += _heapStart * handleIncrement;

    //Load descriptors
    auto currentSlot = _heapStart;
    for (auto& descriptor : descriptors)
    {
      if (descriptor->TryLoad(handleSlot))
      {
        handleSlot.ptr += handleIncrement;
        currentSlot++;
      }
    }
    
    
    //Set new heap start
    _heapStart = currentSlot;
  }
}