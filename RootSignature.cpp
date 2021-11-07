#include "pch.h"
#include "RootSignature.h"
#include "BitwiseOperations.h"

using namespace std;
using namespace winrt;
using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  RootSignatureFactory::RootSignatureFactory(const winrt::com_ptr<ID3D12DeviceT>& device) :
    GraphicsResource(device)
  { }

  RootSignatureInitializationContext::RootSignatureInitializationContext(const RootSignatureFactory* factory) :
    _factory(factory)
  { }
  
  RootSignatureInitializationContext::~RootSignatureInitializationContext()
  {
    auto signatureBlob = _signature->Serialize();
    check_hresult(_factory->Device()->CreateRootSignature(
      0,
      signatureBlob->GetBufferPointer(),
      signatureBlob->GetBufferSize(),
      guid_of<ID3D12RootSignature>(),
      _signature->_rootSignature.put_void()
    ));
  }

  RootSignatureBase::RootSignatureBase(RootSignatureInitializationContext& context)
  { 
    context._signature = this;
  }

  RootSignatureBase::RootSignatureBase(RootSignatureInitializationContext& context, std::vector<StaticSampler>&& staticSamplers) :
    RootSignatureBase(context)
  { 
    _staticSamplers = move(staticSamplers);
  }

  ID3D12RootSignature* RootSignatureBase::Signature() const
  {
    return _rootSignature.get();
  }

  uint32_t RootSignatureBase::AddParameter(RootSignatureParameter* parameter)
  {
    auto index = uint32_t(_parameters.size());
    _parameters.push_back(parameter);
    return index;
  }

  winrt::com_ptr<ID3DBlob> RootSignatureBase::Serialize() const
  {
    //Prepare root signature description
    Infrastructure::value_bag bag;
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc;
    zero_memory(desc);
    desc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;

    //Set flags
    desc.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
    if (IsInputAssemblerEnabled) desc.Desc_1_1.Flags |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    
    //Add parameters
    desc.Desc_1_1.NumParameters = uint32_t(_parameters.size());    
    auto& parameters = bag.add<vector<D3D12_ROOT_PARAMETER1>>();
    parameters.reserve(_parameters.size());
    for (auto& parameter : _parameters)
    {
      parameters.push_back(parameter->GetDescription(bag));
    }
    desc.Desc_1_1.pParameters = parameters.data();
    
    //Serialize description
    com_ptr<ID3DBlob> result;
    check_hresult(D3D12SerializeVersionedRootSignature(&desc, result.put(), nullptr));
    return result;
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
  
  StaticSampler::StaticSampler(uint32_t slot, TextureFilter filter, UvwAddressMode addressMode, ShaderVisibility visibility) :
    _slot(slot),
    _filter(filter),
    _addressMode(addressMode),
    _visibility(visibility)
  { }

  D3D12_STATIC_SAMPLER_DESC StaticSampler::GetDescription() const
  {
    D3D12_STATIC_SAMPLER_DESC desc;
    zero_memory(desc);

    desc.Filter = D3D12_FILTER(_filter);
    desc.AddressU = D3D12_TEXTURE_ADDRESS_MODE(_addressMode.U);
    desc.AddressV = D3D12_TEXTURE_ADDRESS_MODE(_addressMode.V);
    desc.AddressW = D3D12_TEXTURE_ADDRESS_MODE(_addressMode.W);
    desc.MaxAnisotropy = _filter == TextureFilter::Anisotropic ? 8 : 1;
    desc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    desc.MaxLOD = D3D12_FLOAT32_MAX;
    desc.ShaderRegister = _slot;
    desc.ShaderVisibility = D3D12_SHADER_VISIBILITY(_visibility);

    return desc;
  }
}