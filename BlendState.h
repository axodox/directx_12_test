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
    friend class PipelineStateFactory;

  public:
    constexpr BlendState(BlendType type);

    static const BlendState Opaque;
    static const BlendState Additive;
    static const BlendState Subtractive;
    static const BlendState AlphaBlend;

  private:
    D3D12_BLEND_DESC _description;
    uint32_t _sampleMask = 0xffffffff;
  };
}