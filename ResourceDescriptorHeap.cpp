#include "pch.h"
#include "ResourceDescriptorHeap.h"

using namespace std;

namespace dx12test::Graphics
{
  DescriptorHeapType ResourceDescriptorHeap::Type() const
  {
    return DescriptorHeapType::Resource;
  }

  std::shared_ptr<ConstantBufferView> ResourceDescriptorHeap::AddConstantBufferView(const std::shared_ptr<ConstantBuffer>& resource)
  {
    auto result = make_shared<ConstantBufferView>(resource);
    AddDescriptorHeapItem(result);
    return result;
  }
}