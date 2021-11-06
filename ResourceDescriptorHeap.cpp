#include "pch.h"
#include "ResourceDescriptorHeap.h"

namespace dx12test::Graphics
{
  DescriptorHeapType ResourceDescriptorHeap::Type() const
  {
    return DescriptorHeapType::Resource;
  }
}