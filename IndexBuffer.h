#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  class CommandListBuilder;

  struct IndexBufferInitializationContext
  {
    virtual D3D12_INDEX_BUFFER_VIEW GetView() const = 0;
  };

  template<typename T>
  struct IndexData : public ArrayBufferData<T>, IndexBufferInitializationContext
  { 
    using ArrayBufferData<T>::ArrayBufferData;

    virtual const void* InitializationContext() const override
    {
      return (IndexBufferInitializationContext*)this;
    }

    virtual D3D12_INDEX_BUFFER_VIEW GetView() const override
    {
      D3D12_INDEX_BUFFER_VIEW view;
      view.SizeInBytes = Capacity();
      view.Format = sizeof(T) == 16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
      return view;
    }
  };

  template<typename T>
  struct IndexPlaceholder : public ArrayBufferPlaceholder<T>, IndexBufferInitializationContext
  { 
    using ArrayBufferData<T>::ArrayBufferData;

    virtual const void* InitializationContext() const override
    {
      return (IndexBufferInitializationContext*)this;
    }

    virtual D3D12_INDEX_BUFFER_VIEW GetView() const override
    {
      D3D12_INDEX_BUFFER_VIEW view;
      view.SizeInBytes = Capacity();
      view.Format = sizeof(T) == 16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
      return view;
    }
  };

  class IndexBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;
    void Set(CommandListBuilder& commandList) const;

  protected:
    virtual void OnInitialize(const void* context) override;
    virtual D3D12_RESOURCE_STATES DefaultState() const override;

  private:
    D3D12_INDEX_BUFFER_VIEW _view;
  };
}