#pragma once
#include "pch.h"

namespace dx12test
{
  enum class PrimitiveTopology : std::underlying_type_t<D3D12_PRIMITIVE_TOPOLOGY_TYPE>
  {
    Undefined = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,
    Point = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,
    Line = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,
    Triangle = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
    Patch = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH
  };
}