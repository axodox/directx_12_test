#include "pch.h"
#include "VertexBuffer.h"

namespace dx12test::Graphics
{
  ResourceType VertexBuffer::Type() const
  {
    return ResourceType::VertexBuffer;
  }

  D3D12_RESOURCE_STATES VertexBuffer::DefaultState() const
  {
    return D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
  }
}