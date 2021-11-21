#include "pch.h"
#include "IndexBuffer.h"
#include "CommandListBuilder.h"

namespace dx12test::Graphics
{
  ResourceType IndexBuffer::Type() const
  {
    return ResourceType::IndexBuffer;
  }

  void IndexBuffer::Set(CommandListBuilder& commandList) const
  {
    commandList.Resource()->IASetIndexBuffer(&_view);
  }
  
  void IndexBuffer::OnInitialize(const void* context)
  {
    _view = static_cast<const IndexBufferInitializationContext*>(context)->GetView();
    _view.BufferLocation = _resource->GetGPUVirtualAddress();
  }

  D3D12_RESOURCE_STATES IndexBuffer::DefaultState() const
  {
    return D3D12_RESOURCE_STATE_INDEX_BUFFER;
  }
}