#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum BlendType
  {
    Opaque,
    Additive,
    Subtractive,
    AlphaBlend
  };

  class BlendState
  {
    friend class GraphicsPipelineStateBuilder;

  public:
    BlendState(BlendType type);

  private:
    D3D12_BLEND_DESC _description;
    uint32_t _sampleMask = 0xffffffff;
  };
}