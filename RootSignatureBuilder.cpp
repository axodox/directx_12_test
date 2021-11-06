#include "pch.h"
#include "RootSignatureBuilder.h"
#include "BitwiseOperations.h"

using namespace std;
using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  uint32_t RootSignatureBase::AddParameter(RootSignatureParameter* parameter)
  {
    auto index = uint32_t(_parameters.size());
    _parameters.push_back(parameter);
    return index;
  }

  D3D12_ROOT_SIGNATURE_DESC1 RootSignatureBase::GetDescription(Infrastructure::value_bag& bag) const
  {
    D3D12_ROOT_SIGNATURE_DESC1 desc;
    zero_memory(desc);
    desc.NumParameters = uint32_t(_parameters.size());
    
    auto& parameters = bag.add<vector<D3D12_ROOT_PARAMETER1>>();
    parameters.reserve(_parameters.size());
    for (auto& parameter : _parameters)
    {
      parameters.push_back(parameter->GetDescription(bag));
    }
    desc.pParameters = parameters.data();

    return desc;
  }

  RootSignatureParameter::RootSignatureParameter(RootSignatureBase* owner, ShaderVisibility visibility) :
    _owner(owner),
    _index(_owner->AddParameter(this)),
    _visibility(visibility)
  { }

  D3D12_ROOT_PARAMETER1 RootSignatureParameter::GetDescription(Infrastructure::value_bag& bag) const
  {
    D3D12_ROOT_PARAMETER1 desc;
    zero_memory(desc);

    desc.ShaderVisibility = D3D12_SHADER_VISIBILITY(_visibility);
    FillDescription(bag, desc);
    return desc;
  }

  SingleSlotParameter::SingleSlotParameter(RootSignatureBase* owner, uint32_t slot, ShaderVisibility visibility) :
    RootSignatureParameter(owner, visibility),
    _slot(slot)
  { }

  void SingleSlotParameter::FillDescription(Infrastructure::value_bag& bag, D3D12_ROOT_PARAMETER1& parameter) const
  {
    parameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    parameter.DescriptorTable.NumDescriptorRanges = 1;
    
    auto& range = bag.add<D3D12_DESCRIPTOR_RANGE1>();
    zero_memory(range);
    range.BaseShaderRegister = _slot;
    range.NumDescriptors = 1;
    switch (Type())
    {
    case RootSignatureParameterType::ShaderResourceView:
      range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
      break;
    case RootSignatureParameterType::UnorderedAccessView:
      range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
      break;
    case RootSignatureParameterType::ConstantBufferView:
      range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
      break;
    case RootSignatureParameterType::Sampler:
      range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
      break;
    }
    
    parameter.DescriptorTable.pDescriptorRanges = &range;
  }

  RootSignatureParameterType ShaderResourceViewParameter::Type() const
  {
    return RootSignatureParameterType::ShaderResourceView;
  }

  RootSignatureParameterType UnorderedAccessViewParameter::Type() const
  {
    return RootSignatureParameterType::UnorderedAccessView;
  }

  RootSignatureParameterType ConstantBufferViewParameter::Type() const
  {
    return RootSignatureParameterType::ConstantBufferView;
  }

  RootSignatureParameterType SamplerParameter::Type() const
  {
    return RootSignatureParameterType::Sampler;
  }
}