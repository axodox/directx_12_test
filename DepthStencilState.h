#pragma once
#include "ComparisonFunction.h"

namespace dx12test::Graphics
{
  class DepthStencilState
  {
    friend class PipelineStateFactory;

  public:
    constexpr DepthStencilState(bool depthWrite = true, ComparisonFunction depthFunc = ComparisonFunction::Less);

    static const DepthStencilState Default;

  private:
    D3D12_DEPTH_STENCIL_DESC _description;
  };
}