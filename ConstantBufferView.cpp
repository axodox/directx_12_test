#include "pch.h"
#include "ConstantBufferView.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  ConstantBufferView::ConstantBufferView(const std::shared_ptr<ConstantBuffer>& buffer) :
    _buffer(buffer)
  { }

  bool ConstantBufferView::OnTryLoad(const DescriptorHeapItemInitializationContext& context)
  {
    //We cannot create view for an uninitialized resource
    if (!_buffer->IsLoaded()) return false;
    auto& resource = _buffer->Resource();

    //Build description
    D3D12_CONSTANT_BUFFER_VIEW_DESC desc;
    zero_memory(desc);
    desc.SizeInBytes = resource->GetDesc().Width;
    desc.BufferLocation = resource->GetGPUVirtualAddress();

    //Create constant buffer view
    context.Device->CreateConstantBufferView(
      &desc,
      context.CpuDescriptorHandle);
  }
}