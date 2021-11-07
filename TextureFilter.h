#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum class TextureFilter : std::underlying_type_t<D3D12_FILTER>
  {
    MinMagMipPoint = D3D12_FILTER_MIN_MAG_MIP_POINT,
    MinMagPoint_MipLinear = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR,
    MinPoint_MagLinear_MipPoint = D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
    MinPoint_MagMipLinear = D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR,
    MinLinear_MagMipPoint = D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT,
    MinLinear_MagPoint_MipLinear = D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
    MinMagLinear_MipPoint = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,
    MinMagMipLinear = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
    Anisotropic = D3D12_FILTER_ANISOTROPIC
  };
}