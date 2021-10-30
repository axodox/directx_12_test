#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  template<typename T>
  using IndexData = ArrayBufferData<T>;

  template<typename T>
  using IndexPlaceholder = ArrayBufferPlaceholder<T>;

  class IndexBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;
    virtual D3D12_RESOURCE_STATES DefaultState() const override;
    virtual void Initialize(const winrt::com_ptr<ID3D12Resource>& resource) override;
  
  };
}