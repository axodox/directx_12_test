#include "pch.h"
#include "RasterizerState.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  RasterizerState::RasterizerState(RasterizerType type, int depthBias, bool isMultisampling)
  {
    zero_memory(_description);

    switch (type)
    {
    case RasterizerType::CullNone:
      _description.CullMode = D3D12_CULL_MODE_NONE;
      _description.FillMode = D3D12_FILL_MODE_SOLID;
      break;
    case RasterizerType::CullClockwise:
      _description.CullMode = D3D12_CULL_MODE_FRONT;
      _description.FillMode = D3D12_FILL_MODE_SOLID;
      break;
    case RasterizerType::CullCounterClockwise:
      _description.CullMode = D3D12_CULL_MODE_BACK;
      _description.FillMode = D3D12_FILL_MODE_SOLID;
      break;
    case RasterizerType::Wireframe:
      _description.CullMode = D3D12_CULL_MODE_NONE;
      _description.FillMode = D3D12_FILL_MODE_WIREFRAME;
      break;
    default:
      throw std::exception("Unknown rasterizer state!");
    }

    _description.DepthClipEnable = true;
    _description.DepthBias = depthBias;
    _description.MultisampleEnable = isMultisampling;
  }
}