#pragma once
#include "GraphicsDefines.h"

namespace dx12test::Graphics
{
  enum class ResourceCategory
  {
    None = 0,
    Buffers = 1,
    Textures = 2,
    RenderTargets = 4
  };

  D3D12_HEAP_FLAGS ToHeapFlags(ResourceCategory category);

  enum class ResourceType
  {
    Unknown,
    IndexBuffer,
    VertexBuffer,
    ConstantBuffer
  };

  ResourceCategory ToResourceCategory(ResourceType resourceType);

  bool AreCompatible(const D3D12_HEAP_DESC& target, const D3D12_HEAP_DESC& source);

  enum class ResourceUsageMode
  {
    Immutable
  };

  class ResourceHeapItem
  {
    friend class ResourceHeapBuilder;

  public:
    virtual ~ResourceHeapItem() = default;
    virtual ResourceType Type() const = 0;

    bool IsLoaded() const;
    const winrt::com_ptr<ID3D12ResourceT>& Resource() const;

  protected:
    virtual void OnInitialize() { }
    virtual D3D12_RESOURCE_STATES DefaultState() const = 0;

  private:
    winrt::com_ptr<ID3D12ResourceT> _resource;

    void Initialize(const winrt::com_ptr<ID3D12ResourceT>& resource);
  };
}