#include "pch.h"
#include "IndexBuffer.h"

using namespace winrt;

namespace dx12test::Graphics
{
  ResourceType IndexBuffer::Type() const
  {
    return ResourceType::IndexBuffer;
  }
  
  D3D12_RESOURCE_STATES IndexBuffer::DefaultState() const
  {
    return D3D12_RESOURCE_STATE_INDEX_BUFFER;
  }
}