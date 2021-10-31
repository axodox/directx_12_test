#pragma once

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

  struct ResourceHeapItem
  {
    virtual ~ResourceHeapItem() = default;

    virtual ResourceType Type() const = 0;
    virtual D3D12_RESOURCE_STATES DefaultState() const = 0;

    const winrt::com_ptr<ID3D12Resource>& Resource() const;
    void Initialize(const winrt::com_ptr<ID3D12Resource>& resource);

  protected:
    virtual void OnInitialize() { }

  private:
    winrt::com_ptr<ID3D12Resource> _resource;
  };
}