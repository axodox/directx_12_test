#pragma once
#include "DescriptorHeap.h"

namespace dx12test::Graphics
{
  class ResourceDescriptorHeap : public DescriptorHeap
  {
  public:
    virtual DescriptorHeapType Type() const override;
  };
}