#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  struct VertexPosition
  {
    DirectX::XMFLOAT3 Position;

    static const std::array<D3D12_INPUT_ELEMENT_DESC, 1> Elements;
  };

  struct VertexPositionNormal
  {
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;

    static const std::array<D3D12_INPUT_ELEMENT_DESC, 2> Elements;
  };

  struct VertexPositionColor
  {
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Color;

    static const std::array<D3D12_INPUT_ELEMENT_DESC, 2> Elements;
  };

  struct VertexPositionTexture
  {
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT2 Texture;

    static const std::array<D3D12_INPUT_ELEMENT_DESC, 2> Elements;
  };

  struct VertexPositionNormalColor
  {
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT3 Color;

    static const std::array<D3D12_INPUT_ELEMENT_DESC, 3> Elements;
  };

  struct VertexPositionNormalTexture
  {
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Texture;

    static const std::array<D3D12_INPUT_ELEMENT_DESC, 3> Elements;
  };

  typedef D3D12_INPUT_LAYOUT_DESC InputLayout;

  template<typename T>
  constexpr InputLayout* LayoutOf()
  {
    static InputLayout layout = {
      T::Elements.data(),
      T::Elements.size()
    };
    return &layout;
  };
}