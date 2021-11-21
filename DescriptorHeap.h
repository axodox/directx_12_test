#pragma once
#include "GraphicsDefines.h"
#include "GraphicsResource.h"

namespace dx12test::Graphics
{
  struct DescriptorHeapItemInitializationContext
  {
    ID3D12DeviceT* Device;
    D3D12_CPU_DESCRIPTOR_HANDLE CpuDescriptorHandle;
    D3D12_GPU_DESCRIPTOR_HANDLE GpuDescriptorHandle;
    size_t Slot;
  };

  class DescriptorHeapItem
  {
    friend class DescriptorHeap;

  public:
    virtual ~DescriptorHeapItem() = default;
    bool IsLoaded() const;

    D3D12_GPU_DESCRIPTOR_HANDLE Handle() const;

  protected:
    virtual bool OnTryLoad(const DescriptorHeapItemInitializationContext& context) = 0;

  private:
    bool TryLoad(const DescriptorHeapItemInitializationContext& context);

    bool _isLoaded = false;
    D3D12_GPU_DESCRIPTOR_HANDLE _handle = { 0 };
  };

  enum class DescriptorHeapType : std::underlying_type_t<D3D12_DESCRIPTOR_HEAP_TYPE>
  {
    Resource = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
    Sampler = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
    RenderTarget = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
    DepthStencil = D3D12_DESCRIPTOR_HEAP_TYPE_DSV
  };

  class DescriptorHeap : public GraphicsResource
  {
    friend class CommandListBuilder;

  public:
    DescriptorHeap(const winrt::com_ptr<ID3D12DeviceT>& device);
    virtual ~DescriptorHeap() = default;

    virtual DescriptorHeapType Type() const = 0;

    void Rebuild();

  protected:
    void AddDescriptorHeapItem(const std::shared_ptr<DescriptorHeapItem>& heapItem);

  private:
    std::vector<std::shared_ptr<DescriptorHeapItem>> CleanUpAndLockDescriptors();
    void AllocateHeapSpace(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors);
    void PopulateHeap(const std::vector<std::shared_ptr<DescriptorHeapItem>>& descriptors);

    std::mutex _mutex;
    winrt::com_ptr<ID3D12DescriptorHeap> _heap;
    std::vector<std::weak_ptr<DescriptorHeapItem>> _items;
    size_t _heapSize = 0, _heapStart = 0;
  };
}