#include "pch.h"
#include "RasterizerState.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  constexpr RasterizerState::RasterizerState(RasterizerType type, int depthBias, bool isMultisampling)
  {
    switch (type)
    {
    case RasterizerType::Default:
      _description.CullMode = D3D12_CULL_MODE_BACK;
      _description.FillMode = D3D12_FILL_MODE_SOLID;
      break;
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
    _description.FrontCounterClockwise = false;

    _description.DepthClipEnable = true;
    _description.DepthBias = depthBias;
    _description.DepthBiasClamp = 0.f;
    _description.DepthClipEnable = false;

    _description.MultisampleEnable = isMultisampling;
    _description.AntialiasedLineEnable = false;
    _description.ForcedSampleCount = 0;
    _description.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
  }

  const RasterizerState RasterizerState::Default = { RasterizerType::Default };
  const RasterizerState RasterizerState::CullNone = { RasterizerType::CullNone };
  const RasterizerState RasterizerState::CullClockwise = { RasterizerType::CullClockwise };
  const RasterizerState RasterizerState::CullCounterClockwise = { RasterizerType::CullCounterClockwise };
  const RasterizerState RasterizerState::Wireframe = { RasterizerType::Wireframe };
}