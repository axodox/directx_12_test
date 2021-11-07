#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  struct MultiSamplingState : public DXGI_SAMPLE_DESC
  {
    static const MultiSamplingState Single;
  };
}