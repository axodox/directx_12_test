#pragma once
#include "DescriptorHeap.h"
#include "ConstantBuffer.h"

namespace dx12test::Graphics
{
  class ConstantBufferView : public DescriptorHeapItem
  {
  public:
    ConstantBufferView(const std::shared_ptr<ConstantBuffer>& buffer);

  protected:
    virtual bool OnTryLoad(const DescriptorHeapItemInitializationContext& context) override;

  private:
    std::shared_ptr<ConstantBuffer> _buffer;
  };
}