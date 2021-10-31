#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"

namespace dx12test::Graphics
{
  template<typename T>
  struct ConstantData : public ValueBufferData<T>
  {
    using ValueBufferData<T>::ValueBufferData;
  };

  template<typename T>
  struct ConstantPlaceholder : public ValueBufferPlaceholder<T>
  {
    using ValueBufferPlaceholder<T>::ValueBufferPlaceholder;
  };

  class ConstantBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;
    virtual D3D12_RESOURCE_STATES DefaultState() const override;
  };
}