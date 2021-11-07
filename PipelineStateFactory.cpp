#include "pch.h"
#include "PipelineStateFactory.h"
#include "BitwiseOperations.h"

using namespace std;
using namespace winrt;
using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  PipelineState::PipelineState(const winrt::com_ptr<ID3D12PipelineState>& state) :
    _state(state)
  { }

  PipelineStateFactory::PipelineStateFactory(const winrt::com_ptr<ID3D12DeviceT>& device) :
    GraphicsResource(device)
  { }

  PipelineState PipelineStateFactory::Create(const GraphicsPipelineStateDescription & description)
  {
    //Build description
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc;
    zero_memory(desc);

    if(!description.RootSignature) throw exception("Root signature must be set."); 
    desc.pRootSignature = description.RootSignature->Signature();

    if(description.VertexShader) desc.VS = description.VertexShader->ByteCode();
    if(description.PixelShader) desc.PS = description.PixelShader->ByteCode();
    if(description.DomainShader) desc.DS = description.DomainShader->ByteCode();
    if(description.HullShader) desc.HS = description.HullShader->ByteCode();
    if(description.GeometryShader) desc.GS = description.GeometryShader->ByteCode();
    
    if(!description.BlendState) throw exception("Blend state must be set.");
    desc.BlendState = description.BlendState->_description;
    desc.SampleMask = description.BlendState->_sampleMask;

    if(!description.RasterizerState) throw exception("Rasterizer state must be set.");
    desc.RasterizerState = description.RasterizerState->_description;

    if(!description.DepthStencilState) throw exception("Depth stencil state must be set.");
    desc.DepthStencilState = description.DepthStencilState->_description;

    if (!description.InputLayout) throw exception("Input layout must be set."); 
    desc.InputLayout = *description.InputLayout;
    desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE(description.Topology);

    desc.NumRenderTargets = UINT(description.RenderTargetFormats.size());
    memcpy(desc.RTVFormats, description.RenderTargetFormats.data(), sizeof(DXGI_FORMAT) * description.RenderTargetFormats.size());
    desc.DSVFormat = DXGI_FORMAT(description.DepthStencilFormat);        
    desc.SampleDesc = description.SamplingState;

    //Create pipeline state
    com_ptr<ID3D12PipelineState> state;
    check_hresult(_device->CreateGraphicsPipelineState(&desc, guid_of<ID3D12PipelineState>(), state.put_void()));
    return PipelineState(move(state));
  }
}