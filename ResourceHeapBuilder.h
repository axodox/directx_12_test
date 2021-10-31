#pragma once
#include "GraphicsResource.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

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
      const GraphicsData* SourceData;
      ResourceHeapItem* HeapItem;
    };

    ResourceHeapData& NewComponent();

    template<typename THeapItem, typename TSourceData>
    std::unique_ptr<THeapItem> AddHeapItem(ResourceUsageMode usageMode, const TSourceData& data = nullptr)
    {
      auto result = std::make_unique<THeapItem>();

      auto& component = NewComponent();
      component.UsageMode = usageMode;
      component.SourceData = &data;
      component.HeapItem = result.get();
      return result;
    }

  public:
    ResourceHeapBuilder(HeapContentKind contentKind, const winrt::com_ptr<ID3D12CommandQueue>& copyQueue);
    HeapContentKind Kind() const;

    template<typename T>
    std::unique_ptr<IndexBuffer> AddIndexBuffer(ResourceUsageMode usageMode, const IndexData<T>& data)
    {
      return AddHeapItem<IndexBuffer>(usageMode, data);
    }

    template<typename T>
    std::unique_ptr<IndexBuffer> AddIndexBuffer(ResourceUsageMode usageMode, const IndexPlaceholder<T>& data)
    {
      return AddHeapItem<IndexBuffer>(usageMode, data);
    }

    template<typename T>
    std::unique_ptr<VertexBuffer> AddVertexBuffer(ResourceUsageMode usageMode, const VertexData<T>& data)
    {
      return AddHeapItem<VertexBuffer>(usageMode, data);
    }

    template<typename T>
    std::unique_ptr<VertexBuffer> AddVertexBuffer(ResourceUsageMode usageMode, const VertexPlaceholder<T>& data)
    {
      return AddHeapItem<VertexBuffer>(usageMode, data);
    }

    template<typename T>
    std::unique_ptr<ConstantBuffer> AddConstantBuffer(ResourceUsageMode usageMode, const ConstantData<T>& data)
    {
      return AddHeapItem<ConstantBuffer>(usageMode, data);
    }

    template<typename T>
    std::unique_ptr<ConstantBuffer> AddConstantBuffer(ResourceUsageMode usageMode, const ConstantPlaceholder<T>& data)
    {
      return AddHeapItem<ConstantBuffer>(usageMode, data);
    }

    [[nodiscard]]
    winrt::com_ptr<ID3D12HeapT> Build();

  private:
    HeapContentKind _heapKind;
    std::list<ResourceHeapData> _components;
    winrt::com_ptr<ID3D12CommandQueue> _copyQueue;
  };
}