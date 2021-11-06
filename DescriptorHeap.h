#pragma once
#include "GraphicsDefines.h"

namespace dx12test::Graphics
{
  class DescriptorHeapItem
  {
  public:
    virtual ~DescriptorHeapItem() = default;

    virtual bool TryLoad(D3D12_CPU_DESCRIPTOR_HANDLE handle) = 0;
    virtual bool IsLoaded() const = 0;
    virtual void Unload() = 0;
  };

  enum class DescriptorHeapType : std::underlying_type_t<D3D12_DESCRIPTOR_HEAP_TYPE>
  {
    Resource = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
    Sampler = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER
  };

  class DescriptorHeap
  {
  public:
    DescriptorHeap(const winrt::com_ptr<ID3D12DeviceT>& device);
    virtual ~DescriptorHeap() = default;

    virtual DescriptorHeapType Type() const = 0;

    void Rebuild();

  private:
    std::mutex _mutex;
    winrt::com_ptr<ID3D12DeviceT> _device;
    winrt::com_ptr<ID3D12DescriptorHeap> _defaultHeap, _uploadHeap;
    size_t _heapSize = 0, _heapStart = 0;

    std::vector<std::weak_ptr<DescriptorHeapItem>> _items;

    std::vector<std::shared_ptr<DescriptorHeapItem>> CleanUpAndLockDescriptors();
    void AllocateHeapSpace(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors);
    void PopulateHeap(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors);
  };
}