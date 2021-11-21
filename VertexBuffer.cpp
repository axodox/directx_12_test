#include "pch.h"
#include "VertexBuffer.h"
#include "CommandListBuilder.h"

namespace dx12test::Graphics
{
  ResourceType VertexBuffer::Type() const
  {
    return ResourceType::VertexBuffer;
  }

  void VertexBuffer::Set(CommandListBuilder& commandList, uint32_t slot) const
  {
    commandList.Resource()->IASetVertexBuffers(slot, 1, &_view);
  }

  void VertexBuffer::OnInitialize(const void* context)
  {
    _view = static_cast<const VertexBufferInitializationContext*>(context)->GetView();
    _view.BufferLocation = _resource->GetGPUVirtualAddress();
  }

  D3D12_RESOURCE_STATES VertexBuffer::DefaultState() const
  {
    return D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
  }
}