#pragma once
#include "DescriptorHeap.h"
#include "ConstantBufferView.h"

namespace dx12test::Graphics
{
  class ResourceDescriptorHeap : public DescriptorHeap
  {
  public:
    using DescriptorHeap::DescriptorHeap;

    virtual DescriptorHeapType Type() const override;

    std::shared_ptr<ConstantBufferView> AddConstantBufferView(const std::shared_ptr<ConstantBuffer>& resource);
  };
}