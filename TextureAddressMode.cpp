#include "pch.h"
#include "TextureAddressMode.h"

namespace dx12test::Graphics
{
  constexpr UvwAddressMode::UvwAddressMode() noexcept :
    U(TextureAddressMode::Wrap),
    V(TextureAddressMode::Wrap),
    W(TextureAddressMode::Wrap)
  { }

  constexpr UvwAddressMode::UvwAddressMode(TextureAddressMode mode) noexcept :
    U(mode),
    V(mode),
    W(mode)
  { }

  constexpr UvwAddressMode::UvwAddressMode(TextureAddressMode modeU, TextureAddressMode modeV, TextureAddressMode modeW) noexcept :
    U(modeU),
    V(modeV),
    W(modeW)
  { }

  const UvwAddressMode UvwAddressMode::Wrap = { TextureAddressMode::Wrap };
  const UvwAddressMode UvwAddressMode::Mirror = { TextureAddressMode::Mirror };
  const UvwAddressMode UvwAddressMode::Clamp = { TextureAddressMode::Clamp };
  const UvwAddressMode UvwAddressMode::Border = { TextureAddressMode::Border };
  const UvwAddressMode UvwAddressMode::MirrorOnce = { TextureAddressMode::MirrorOnce };
}