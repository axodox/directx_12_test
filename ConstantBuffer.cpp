#include "pch.h"
#include "ConstantBuffer.h"

namespace dx12test::Graphics
{
  ResourceType ConstantBuffer::Type() const
  {
    return ResourceType::ConstantBuffer;
  }

  D3D12_RESOURCE_STATES ConstantBuffer::DefaultState() const
  {
    return D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
  }
}