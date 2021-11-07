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
    friend class PipelineStateFactory;

  public:
    constexpr RasterizerState(RasterizerType type, int depthBias = 0, bool isMultisampling = false);

    static const RasterizerState Default;
    static const RasterizerState CullNone;
    static const RasterizerState CullClockwise;
    static const RasterizerState CullCounterClockwise;
    static const RasterizerState Wireframe;

  private:
    D3D12_RASTERIZER_DESC _description;
  };
}