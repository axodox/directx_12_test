#pragma once
#include "BitwiseOperations.h"
#include "GraphicsResource.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

namespace dx12test::Graphics
{
  class ResourceHeapBuilder : public GraphicsResource
  {
    struct ResourceHeapData
    {
      const GraphicsData* SourceData;
      ResourceHeapItem* HeapItem;
    };

    ResourceHeapData& NewComponent();

    template<typename THeapItem, typename TSourceData>
    std::unique_ptr<THeapItem> AddHeapItem(const TSourceData& data = nullptr)
    {
      auto result = std::make_unique<THeapItem>();
      if (!BitwiseOperations::has_flag(_heapKind, ToResourceCategory(result->Type())))
      {
        throw std::logic_error("This resource heap does not support the specified resource category.");
      }

      auto& component = NewComponent();
      component.SourceData = &data;
      component.HeapItem = result.get();
      return result;
    }

  public:
    ResourceHeapBuilder(ResourceCategory contentKind, const winrt::com_ptr<ID3D12CommandQueue>& copyQueue);
    ResourceCategory Kind() const;

    template<typename T>
    std::unique_ptr<IndexBuffer> AddIndexBuffer(const IndexData<T>& data)
    {
      return AddHeapItem<IndexBuffer>(data);
    }

    template<typename T>
    std::unique_ptr<IndexBuffer> AddIndexBuffer(const IndexPlaceholder<T>& data)
    {
      return AddHeapItem<IndexBuffer>(data);
    }

    template<typename T>
    std::unique_ptr<VertexBuffer> AddVertexBuffer(const VertexData<T>& data)
    {
      return AddHeapItem<VertexBuffer>(data);
    }

    template<typename T>
    std::unique_ptr<VertexBuffer> AddVertexBuffer(const VertexPlaceholder<T>& data)
    {
      return AddHeapItem<VertexBuffer>(data);
    }

    template<typename T>
    std::unique_ptr<ConstantBuffer> AddConstantBuffer(const ConstantData<T>& data)
    {
      return AddHeapItem<ConstantBuffer>(data);
    }

    template<typename T>
    std::unique_ptr<ConstantBuffer> AddConstantBuffer(const ConstantPlaceholder<T>& data)
    {
      return AddHeapItem<ConstantBuffer>(data);
    }

    [[nodiscard]]
    winrt::com_ptr<ID3D12HeapT> Build();

  private:
    ResourceCategory _heapKind;
    std::list<ResourceHeapData> _components;
    winrt::com_ptr<ID3D12CommandQueue> _copyQueue;
  };
}