#pragma once
#include "RootSignature.h"
#include "GraphicsResource.h"
#include "Shaders.h"
#include "BlendState.h"
#include "RasterizerState.h"
#include "DepthStencilState.h"

namespace dx12test::Graphics
{
  class GraphicsPipelineStateDescription
  {
    RootSignatureBase* RootSignature = nullptr;

    VertexShader* VertexShader = nullptr;
    HullShader* HullShader = nullptr;
    DomainShader* DomainShader = nullptr;
    GeometryShader* GeometryShader = nullptr;
    PixelShader* PixelShader = nullptr;

    BlendState* BlendState = nullptr;
    RasterizerState* RasterizerState = nullptr;
    DepthStencilState* DepthStencilState = nullptr;
  };

  class GraphicsPipelineStateBuilder : public GraphicsResource
  {
  public:
    GraphicsPipelineStateBuilder(const winrt::com_ptr<ID3D12DeviceT>& device);


  };
}