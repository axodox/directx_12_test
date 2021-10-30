#pragma once
#include "GraphicsResource.h"
#include "IndexBuffer.h"

namespace dx12test::Graphics
{
  enum class HeapContentKind
  {
    None = 0,
    Buffers = 1,
    Textures = 2,
    RenderTargets = 4
  };

  class ResourceHeapBuilder : public GraphicsResource
  {
    struct ResourceHeapData
    {
      ResourceUsageMode UsageMode;
      std::shared_ptr<GraphicsData> SourceData;
      std::shared_ptr<ResourceHeapItem> HeapItem;
    };

    ResourceHeapData& NewComponent();

    template<typename THeapItem, typename TSourceData>
    std::shared_ptr<IndexBuffer> AddHeapItem(ResourceUsageMode usageMode, const std::shared_ptr<TSourceData>& data = nullptr)
    {
      auto result = std::make_shared<THeapItem>();

      auto& component = NewComponent();
      component.UsageMode = usageMode;
      component.SourceData = std::static_pointer_cast<GraphicsData>(data);
      component.HeapItem = result;
      return result;
    }

  public:
    ResourceHeapBuilder(HeapContentKind contentKind, const winrt::com_ptr<ID3D12CommandQueue>& copyQueue);
    HeapContentKind Kind() const;

    template<typename T>
    std::shared_ptr<IndexBuffer> AddIndexBuffer(ResourceUsageMode usageMode, const std::shared_ptr<IndexData<T>>& data)
    {
      return AddHeapItem<IndexBuffer>(usageMode, data);
    }

    template<typename T>
    std::shared_ptr<IndexBuffer> AddIndexBuffer(ResourceUsageMode usageMode, const std::shared_ptr<IndexPlaceholder<T>>& data)
    {
      return AddHeapItem<IndexBuffer>(usageMode, data);
    }

    void Build();

  private:
    HeapContentKind _heapKind;
    std::list<ResourceHeapData> _components;
    winrt::com_ptr<ID3D12CommandQueue> _copyQueue;
  };
}