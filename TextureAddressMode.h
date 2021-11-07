#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum class TextureAddressMode : std::underlying_type_t<D3D12_TEXTURE_ADDRESS_MODE>
  {
    Wrap = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
    Mirror = D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
    Clamp = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
    Border = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
    MirrorOnce = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE
  };

  struct UvwAddressMode
  {
    TextureAddressMode U, V, W;

    constexpr UvwAddressMode() noexcept;
    constexpr UvwAddressMode(TextureAddressMode mode) noexcept;
    constexpr UvwAddressMode(TextureAddressMode modeU, TextureAddressMode modeV, TextureAddressMode modeW)  noexcept;

    static const UvwAddressMode Wrap;
    static const UvwAddressMode Mirror;
    static const UvwAddressMode Clamp;
    static const UvwAddressMode Border;
    static const UvwAddressMode MirrorOnce;
  };
}