#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  template<typename T>
  struct IndexData : public ArrayBufferData<T>
  { 
    using ArrayBufferData<T>::ArrayBufferData;
  };

  template<typename T>
  struct IndexPlaceholder : public ArrayBufferPlaceholder<T>
  { 
    using ArrayBufferData<T>::ArrayBufferData;
  };

  class IndexBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;

  private:
    virtual D3D12_RESOURCE_STATES DefaultState() const override;  
  };
}