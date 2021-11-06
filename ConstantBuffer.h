#pragma once
#include "GraphicsDefines.h"
#include "GraphicsData.h"
#include "ResourceHeapItem.h"
#include "BitwiseOperations.h"

namespace dx12test::Graphics
{
  template<typename T>
  struct ConstantData : public ValueBufferData<T>
  {
    using ValueBufferData<T>::ValueBufferData;

    virtual size_t Capacity() const override
    {
      return BitwiseOperations::align_size(Length(), 256);
    }
  };

  template<typename T>
  struct ConstantPlaceholder : public ValueBufferPlaceholder<T>
  {
    using ValueBufferPlaceholder<T>::ValueBufferPlaceholder;

    virtual size_t Capacity() const override
    {
      return BitwiseOperations::align_size(Length(), 256);
    }
  };

  class ConstantBuffer : public ResourceHeapItem
  {
  public:
    virtual ResourceType Type() const override;

  private:
    virtual D3D12_RESOURCE_STATES DefaultState() const override;
  };
}