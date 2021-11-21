#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  class CommandListBuilder;

  struct VertexBufferInitializationContext
  {
    virtual D3D12_VERTEX_BUFFER_VIEW GetView() const = 0;
  };

  template<typename T>
  struct VertexData : public ArrayBufferData<T>, VertexBufferInitializationContext
  {
    using ArrayBufferData<T>::ArrayBufferData;

    virtual const void* InitializationContext() const override
    {
      return (VertexBufferInitializationContext*)this;
    }

    virtual D3D12_VERTEX_BUFFER_VIEW GetView() const override
    {
      D3D12_VERTEX_BUFFER_VIEW view{};
      view.SizeInBytes = Capacity();
      view.StrideInBytes = sizeof(T);
      return view;
    }
  };

  template<typename T>
  struct VertexPlaceholder : public ArrayBufferPlaceholder<T>, VertexBufferInitializationContext
  {
    using ArrayBufferData<T>::ArrayBufferData;

    virtual const void* InitializationContext() const override
    {
      return (VertexBufferInitializationContext*)this;
    }

    virtual D3D12_VERTEX_BUFFER_VIEW GetView() const override
    {
      D3D12_VERTEX_BUFFER_VIEW view{};
      view.SizeInBytes = sizeof(T);
      view.StrideInBytes = Capacity();
      return view;
    }
  };

  class VertexBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;
    void Set(CommandListBuilder& commandList, uint32_t slot = 0) const;

  protected:
    virtual void OnInitialize(const void* context) override;
    virtual D3D12_RESOURCE_STATES DefaultState() const override;

  private:
    D3D12_VERTEX_BUFFER_VIEW _view;
  };
}