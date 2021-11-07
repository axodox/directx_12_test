#pragma once
#include "GraphicsDefines.h"
#include "GraphicsResource.h"
#include "ValueBag.h"
#include "TextureFilter.h"
#include "TextureAddressMode.h"

namespace dx12test::Graphics
{
  struct RootSignatureBase;
  struct StaticSampler;
  struct RootSignatureParameter;
  struct RootSignatureInitializationContext;

  struct RootSignatureFactory : public GraphicsResource
  {
    RootSignatureFactory(const winrt::com_ptr<ID3D12DeviceT>& device);

    template<typename T>
    std::unique_ptr<T> Create()
    {
      RootSignatureInitializationContext context{ this };
      return std::make_unique<T>(context);
    }
  };

  struct RootSignatureInitializationContext
  {
    friend struct RootSignatureFactory;
    friend struct RootSignatureBase;

    ~RootSignatureInitializationContext();

  private:
    RootSignatureInitializationContext(const RootSignatureFactory* factory);

    const RootSignatureFactory* _factory;
    RootSignatureBase* _signature;
  };

  struct RootSignatureBase
  {
    friend struct RootSignatureParameter;
    friend struct RootSignatureInitializationContext;
    virtual ~RootSignatureBase() = default;

    ID3D12RootSignature* Signature() const;

    bool IsInputAssemblerEnabled = true;

  protected:
    RootSignatureBase(RootSignatureInitializationContext& context);
    RootSignatureBase(RootSignatureInitializationContext& context, std::vector<StaticSampler>&& staticSamplers);

  private:
    uint32_t AddParameter(RootSignatureParameter* parameter);
    winrt::com_ptr<ID3DBlob> Serialize() const;

    std::vector<StaticSampler> _staticSamplers;
    std::vector<RootSignatureParameter*> _parameters;
    winrt::com_ptr<ID3D12RootSignature> _rootSignature;
  };

  enum class RootSignatureParameterType
  {
    ShaderResourceView,
    UnorderedAccessView,
    ConstantBufferView,
    Sampler
  };

  enum class ShaderVisibility : std::underlying_type_t<D3D12_SHADER_VISIBILITY>
  {
    All = D3D12_SHADER_VISIBILITY_ALL,
    Vertex = D3D12_SHADER_VISIBILITY_VERTEX,
    Hull = D3D12_SHADER_VISIBILITY_HULL,
    Domain = D3D12_SHADER_VISIBILITY_DOMAIN,
    Geometry = D3D12_SHADER_VISIBILITY_GEOMETRY,
    Pixel = D3D12_SHADER_VISIBILITY_PIXEL,
    Amplification = D3D12_SHADER_VISIBILITY_AMPLIFICATION,
    Mesh = D3D12_SHADER_VISIBILITY_MESH
  };

  struct RootSignatureParameter
  {
    friend struct RootSignatureBase;

    RootSignatureParameter(RootSignatureBase* owner, ShaderVisibility visibility);
    virtual ~RootSignatureParameter() = default;

    virtual RootSignatureParameterType Type() const = 0;

  protected:
    virtual void FillDescription(Infrastructure::value_bag& bag, D3D12_ROOT_PARAMETER1& parameter) const = 0;

  private:
    D3D12_ROOT_PARAMETER1 GetDescription(Infrastructure::value_bag& bag) const;

    RootSignatureBase* _owner;
    uint32_t _index;
    ShaderVisibility _visibility;
  };

  struct SingleSlotParameter : public RootSignatureParameter
  {
    SingleSlotParameter(RootSignatureBase* owner, uint32_t slot, ShaderVisibility visibility = ShaderVisibility::All);

  protected:
    virtual void FillDescription(Infrastructure::value_bag& bag, D3D12_ROOT_PARAMETER1& parameter) const override;

  private:
    uint32_t _slot;
  };

  struct ShaderResourceViewParameter : public SingleSlotParameter
  {
    using SingleSlotParameter::SingleSlotParameter;
    virtual RootSignatureParameterType Type() const override;
  };

  struct UnorderedAccessViewParameter : public SingleSlotParameter
  {
    using SingleSlotParameter::SingleSlotParameter;
    virtual RootSignatureParameterType Type() const override;
  };

  struct ConstantBufferViewParameter : public SingleSlotParameter
  {
    using SingleSlotParameter::SingleSlotParameter;
    virtual RootSignatureParameterType Type() const override;
  };

  struct SamplerParameter : public SingleSlotParameter
  {
    using SingleSlotParameter::SingleSlotParameter;
    virtual RootSignatureParameterType Type() const override;
  };

  struct StaticSampler
  {
    friend struct RootSignatureBase;

    StaticSampler(uint32_t slot, TextureFilter filter, UvwAddressMode addressMode, ShaderVisibility visibility = ShaderVisibility::All);

  private:
    D3D12_STATIC_SAMPLER_DESC GetDescription() const;

    uint32_t _slot;
    TextureFilter _filter;
    UvwAddressMode _addressMode;
    ShaderVisibility _visibility;
  };
}