#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  template<typename T>
  struct VertexData : public ArrayBufferData<T>
  {
    using ArrayBufferData<T>::ArrayBufferData;
  };

  template<typename T>
  struct VertexPlaceholder : public ArrayBufferPlaceholder<T>
  {
    using ArrayBufferData<T>::ArrayBufferData;
  };

  class VertexBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;
    virtual D3D12_RESOURCE_STATES DefaultState() const override;
  };
}