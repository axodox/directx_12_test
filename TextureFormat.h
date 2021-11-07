#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum class TextureFormat : std::underlying_type_t<DXGI_FORMAT>
  {
    Unknown = DXGI_FORMAT_UNKNOWN,
    R32G32B32A32_Typeless = DXGI_FORMAT_R32G32B32A32_TYPELESS,
    R32G32B32A32_Float = DXGI_FORMAT_R32G32B32A32_FLOAT,
    R32G32B32A32_UInt = DXGI_FORMAT_R32G32B32A32_UINT,
    R32G32B32A32_SInt = DXGI_FORMAT_R32G32B32A32_SINT,

    R32G32B32_Typeless = DXGI_FORMAT_R32G32B32_TYPELESS,
    R32G32B32_Float = DXGI_FORMAT_R32G32B32_FLOAT,
    R32G32B32_UInt = DXGI_FORMAT_R32G32B32_UINT,
    R32G32B32_SInt = DXGI_FORMAT_R32G32B32_SINT,

    R16G16B16A16_Typeless = DXGI_FORMAT_R16G16B16A16_TYPELESS,
    R16G16B16A16_Float = DXGI_FORMAT_R16G16B16A16_FLOAT,
    R16G16B16A16_UNorm = DXGI_FORMAT_R16G16B16A16_UNORM,
    R16G16B16A16_UInt = DXGI_FORMAT_R16G16B16A16_UINT,
    R16G16B16A16_SNorm = DXGI_FORMAT_R16G16B16A16_SNORM,
    R16G16B16A16_SInt = DXGI_FORMAT_R16G16B16A16_SINT,

    R32G32_Typeless = DXGI_FORMAT_R32G32_TYPELESS,
    R32G32_Float = DXGI_FORMAT_R32G32_FLOAT,
    R32G32_UInt = DXGI_FORMAT_R32G32_UINT,
    R32G32_SInt = DXGI_FORMAT_R32G32_SINT,
    R32G8X24_Typeless = DXGI_FORMAT_R32G8X24_TYPELESS,

    D32_Float_S8X24_UInt = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
    R32_Float_X8X24_Typeless = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
    X32_Typeless_G8X24_UInt = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,

    R10G10B10A2_Typeless = DXGI_FORMAT_R10G10B10A2_TYPELESS,
    R10G10B10A2_UNorm = DXGI_FORMAT_R10G10B10A2_UNORM,
    R10G10B10A2_UInt = DXGI_FORMAT_R10G10B10A2_UINT,

    R11G11B10_Float = DXGI_FORMAT_R11G11B10_FLOAT,

    R8G8B8A8_Typeless = DXGI_FORMAT_R8G8B8A8_TYPELESS,
    R8G8B8A8_UNorm = DXGI_FORMAT_R8G8B8A8_UNORM,
    R8G8B8A8_UNorm_SRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
    R8G8B8A8_UInt = DXGI_FORMAT_R8G8B8A8_UINT,
    R8G8B8A8_SNorm = DXGI_FORMAT_R8G8B8A8_SNORM,
    R8G8B8A8_SInt = DXGI_FORMAT_R8G8B8A8_SINT,

    R16G16_Typeless = DXGI_FORMAT_R16G16_TYPELESS,
    R16G16_Float = DXGI_FORMAT_R16G16_FLOAT,
    R16G16_UNorm = DXGI_FORMAT_R16G16_UNORM,
    R16G16_UInt = DXGI_FORMAT_R16G16_UINT,
    R16G16_SNorm = DXGI_FORMAT_R16G16_SNORM,
    R16G16_SInt = DXGI_FORMAT_R16G16_SINT,

    R32_Typeless = DXGI_FORMAT_R32_TYPELESS,
    D32_Float = DXGI_FORMAT_D32_FLOAT,
    R32_Float = DXGI_FORMAT_R32_FLOAT,
    R32_UInt = DXGI_FORMAT_R32_UINT,
    R32_SInt = DXGI_FORMAT_R32_SINT,

    R24G8_Typeless = DXGI_FORMAT_R24G8_TYPELESS,
    D24_UNorm_S8_UInt = DXGI_FORMAT_D24_UNORM_S8_UINT,
    R24_UNorm_X8_Typeless = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
    X24_Typeless_G8_UInt = DXGI_FORMAT_X24_TYPELESS_G8_UINT,

    R8G8_Typeless = DXGI_FORMAT_R8G8_TYPELESS,
    R8G8_UNorm = DXGI_FORMAT_R8G8_UNORM,
    R8G8_UInt = DXGI_FORMAT_R8G8_UINT,
    R8G8_SNorm = DXGI_FORMAT_R8G8_SNORM,
    R8G8_SInt = DXGI_FORMAT_R8G8_SINT,

    R16_Typeless = DXGI_FORMAT_R16_TYPELESS,
    R16_Float = DXGI_FORMAT_R16_FLOAT,
    D16_UNorm = DXGI_FORMAT_D16_UNORM,
    R16_UNorm = DXGI_FORMAT_R16_UNORM,
    R16_UInt = DXGI_FORMAT_R16_UINT,
    R16_SNorm = DXGI_FORMAT_R16_SNORM,
    R16_SInt = DXGI_FORMAT_R16_SINT,

    R8_Typeless = DXGI_FORMAT_R8_TYPELESS,
    R8_UNorm = DXGI_FORMAT_R8_UNORM,
    R8_UInt = DXGI_FORMAT_R8_UINT,
    R8_SNorm = DXGI_FORMAT_R8_SNORM,
    R8_SInt = DXGI_FORMAT_R8_SINT,
    A8_UNorm = DXGI_FORMAT_A8_UNORM,

    R1_UNorm = DXGI_FORMAT_R1_UNORM,

    R9G9B9E5_SharedExp = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,

    R8G8_B8G8_UNorm = DXGI_FORMAT_R8G8_B8G8_UNORM,
    G8R8_G8B8_UNorm = DXGI_FORMAT_G8R8_G8B8_UNORM,

    BC1_Typeless = DXGI_FORMAT_BC1_TYPELESS,
    BC1_UNorm = DXGI_FORMAT_BC1_UNORM,
    BC1_UNorm_SRGB = DXGI_FORMAT_BC1_UNORM_SRGB,
    BC2_Typeless = DXGI_FORMAT_BC2_TYPELESS,
    BC2_UNorm = DXGI_FORMAT_BC2_UNORM,
    BC2_UNorm_SRGB = DXGI_FORMAT_BC2_UNORM_SRGB,
    BC3_Typeless = DXGI_FORMAT_BC3_TYPELESS,
    BC3_UNorm = DXGI_FORMAT_BC3_UNORM,
    BC3_UNorm_SRGB = DXGI_FORMAT_BC3_UNORM_SRGB,
    BC4_Typeless = DXGI_FORMAT_BC4_TYPELESS,
    BC4_UNorm = DXGI_FORMAT_BC4_UNORM,
    BC4_SNorm = DXGI_FORMAT_BC4_SNORM,
    BC5_Typeless = DXGI_FORMAT_BC5_TYPELESS,
    BC5_UNorm = DXGI_FORMAT_BC5_UNORM,
    BC5_SNorm = DXGI_FORMAT_BC5_SNORM,

    B5G6R5_UNorm = DXGI_FORMAT_B5G6R5_UNORM,
    B5G5R5A1_UNorm = DXGI_FORMAT_B5G5R5A1_UNORM,

    B8G8R8A8_UNorm = DXGI_FORMAT_B8G8R8A8_UNORM,
    B8G8R8X8_UNorm = DXGI_FORMAT_B8G8R8X8_UNORM,
    R10G10B10_XrBias_A2_UNorm = DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
    B8G8R8A8_Typeless = DXGI_FORMAT_B8G8R8A8_TYPELESS,
    B8G8R8A8_UNorm = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
    B8G8R8X8_Typeless = DXGI_FORMAT_B8G8R8X8_TYPELESS,
    B8G8R8X8_UNorm_SRGB = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,

    BC6H_Typeless = DXGI_FORMAT_BC6H_TYPELESS,
    BC6H_UF16 = DXGI_FORMAT_BC6H_UF16,
    BC6H_SF16 = DXGI_FORMAT_BC6H_SF16,

    BC7_Typeless = DXGI_FORMAT_BC7_TYPELESS,
    BC7_UNorm = DXGI_FORMAT_BC7_UNORM,
    BC7_UNorm_SRGB = DXGI_FORMAT_BC7_UNORM_SRGB,

    AYUV = DXGI_FORMAT_AYUV,
    Y410 = DXGI_FORMAT_Y410,
    Y416 = DXGI_FORMAT_Y416,
    NV12 = DXGI_FORMAT_NV12,
    P010 = DXGI_FORMAT_P010,
    P016 = DXGI_FORMAT_P016,
    X420_Opaque = DXGI_FORMAT_420_OPAQUE,
    YUY2 = DXGI_FORMAT_YUY2,
    Y210 = DXGI_FORMAT_Y210,
    Y216 = DXGI_FORMAT_Y216,
    NV12 = DXGI_FORMAT_NV11,
    AI44 = DXGI_FORMAT_AI44,
    IA44 = DXGI_FORMAT_IA44,

    P8 = DXGI_FORMAT_P8,
    A8P8 = DXGI_FORMAT_A8P8,

    B4G4R4A4_UNorm = DXGI_FORMAT_B4G4R4A4_UNORM,

    P208 = DXGI_FORMAT_P208,
    V208 = DXGI_FORMAT_V208,
    V408 = DXGI_FORMAT_V408,

    SamplerFeedbackMinMipOpaque = DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
    SamplerFeedbackMipRegionUsedOpaque = DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
  };
}