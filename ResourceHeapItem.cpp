#include "pch.h"
#include "ResourceHeapItem.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  D3D12_HEAP_FLAGS ToHeapFlags(ResourceCategory category)
  {
    D3D12_HEAP_FLAGS result = D3D12_HEAP_FLAG_NONE;

    if (!has_flag(category, ResourceCategory::Buffers))
    {
      result |= D3D12_HEAP_FLAG_DENY_BUFFERS;
    }

    if (!has_flag(category, ResourceCategory::Textures))
    {
      result |= D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES;
    }

    if (!has_flag(category, ResourceCategory::RenderTargets))
    {
      result |= D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES;
    }

    return result;
  }

  ResourceCategory ToResourceCategory(ResourceType resourceType)
  {
    switch (resourceType)
    {
    case ResourceType::IndexBuffer:
    case ResourceType::VertexBuffer:
    case ResourceType::ConstantBuffer:
      return ResourceCategory::Buffers;
    default:
      return ResourceCategory::None;
    }
  }

  bool AreCompatible(const D3D12_HEAP_DESC& target, const D3D12_HEAP_DESC& source)
  {
    return 
      target.Alignment == source.Alignment &&
      target.Flags == source.Flags &&
      are_equal(target.Properties, source.Properties) &&
      target.SizeInBytes >= source.SizeInBytes;
  }

  const winrt::com_ptr<ID3D12Resource>& ResourceHeapItem::Resource() const
  {
    return _resource;
  }

  void ResourceHeapItem::Initialize(const winrt::com_ptr<ID3D12Resource>& resource)
  {
    _resource = resource;
    OnInitialize();
  }
}