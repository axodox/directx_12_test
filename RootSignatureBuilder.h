#pragma once
#include "GraphicsDefines.h"
#include "GraphicsResource.h"
#include "ValueBag.h"

namespace dx12test::Graphics
{
  struct RootSignatureParameter;

  class RootSignatureBase
  {
    friend struct RootSignatureParameter;

  public:
    virtual ~RootSignatureBase() = default;

  private:
    uint32_t AddParameter(RootSignatureParameter* parameter);
    D3D12_ROOT_SIGNATURE_DESC1 GetDescription(Infrastructure::value_bag& bag) const;

    std::vector<RootSignatureParameter*> _parameters;
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
  public:
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
}