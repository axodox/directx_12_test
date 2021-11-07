#pragma once
#include "ComparisonFunction.h"

namespace dx12test::Graphics
{
  class DepthStencilState
  {
    friend class GraphicsPipelineStateBuilder;

  public:
    DepthStencilState(bool depthWrite = true, ComparisonFunction depthFunc = ComparisonFunction::Less);

  private:
    D3D12_DEPTH_STENCIL_DESC _description;
  };
}