#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum class ComparisonFunction : std::underlying_type_t<D3D12_COMPARISON_FUNC>
  {
    Never = D3D12_COMPARISON_FUNC_NEVER,
    Less = D3D12_COMPARISON_FUNC_LESS,
    Equal = D3D12_COMPARISON_FUNC_EQUAL,
    LessOrEqual = D3D12_COMPARISON_FUNC_LESS_EQUAL,
    Greater = D3D12_COMPARISON_FUNC_GREATER,
    NotEqual = D3D12_COMPARISON_FUNC_NOT_EQUAL,
    GreaterOrEqual = D3D12_COMPARISON_FUNC_GREATER_EQUAL,
    Always = D3D12_COMPARISON_FUNC_ALWAYS
  };
}