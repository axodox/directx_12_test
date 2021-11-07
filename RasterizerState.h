#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum class RasterizerType : uint8_t
  {
    Default,
    CullNone,
    CullClockwise,
    CullCounterClockwise,
    Wireframe
  };

  class RasterizerState
  {
    friend class GraphicsPipelineStateBuilder;

  public:
    RasterizerState(RasterizerType type, int depthBias, bool isMultisampling);

  private:
    D3D12_RASTERIZER_DESC _description;
  };
}