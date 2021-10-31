#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  struct VertexPosition
  {
    DirectX::XMFLOAT3 Position;

    VertexPosition() = default;
    VertexPosition(const DirectX::XMFLOAT3& position) :
      Position(position)
    { }
  };
}