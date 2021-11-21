#pragma once
#include "RootSignature.h"
#include "GraphicsResource.h"
#include "Shaders.h"
#include "BlendState.h"
#include "RasterizerState.h"
#include "DepthStencilState.h"
#include "VertexDefinitions.h"
#include "PrimitiveTopology.h"
#include "TextureFormat.h"
#include "MultiSamplingState.h"

namespace dx12test::Graphics
{
  struct GraphicsPipelineStateDescription
  {
    const RootSignatureBase* RootSignature = nullptr;

    const VertexShader* VertexShader = nullptr;
    const HullShader* HullShader = nullptr;
    const DomainShader* DomainShader = nullptr;
    const GeometryShader* GeometryShader = nullptr;
    const PixelShader* PixelShader = nullptr;

    const BlendState* BlendState = &BlendState::Opaque;
    const RasterizerState* RasterizerState = &RasterizerState::Default;
    const DepthStencilState* DepthStencilState = &DepthStencilState::Default;

    const InputLayout* InputLayout = nullptr;
    PrimitiveTopology Topology = PrimitiveTopology::Triangle;

    std::vector<TextureFormat> RenderTargetFormats;
    TextureFormat DepthStencilFormat = TextureFormat::Unknown;
    MultiSamplingState SamplingState = MultiSamplingState::Single;
  };

  class PipelineState
  {
    friend class CommandListPool;

  public:
    PipelineState(const winrt::com_ptr<ID3D12PipelineState>& state);

  private:
    winrt::com_ptr<ID3D12PipelineState> _state;
  };

  class PipelineStateFactory : public GraphicsResource
  {
  public:
    PipelineStateFactory(const winrt::com_ptr<ID3D12DeviceT>& device);

    PipelineState Create(const GraphicsPipelineStateDescription& description);
  };
}