#include "pch.h"
#include "BlendState.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  BlendState::BlendState(BlendType type)
  {
    zero_memory(_description);
    
    auto& renderTargetBlendDesc = _description.RenderTarget[0];
    renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    switch (type)
    {
    case BlendType::Opaque:
      renderTargetBlendDesc.BlendEnable = false;
      renderTargetBlendDesc.SrcBlend = D3D12_BLEND_ONE;
      renderTargetBlendDesc.DestBlend = D3D12_BLEND_ZERO;
      renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
      renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
      renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
      renderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
      break;
    case BlendType::Additive:
    case BlendType::Subtractive:
      renderTargetBlendDesc.BlendEnable = true;
      renderTargetBlendDesc.SrcBlend = D3D12_BLEND_ONE;
      renderTargetBlendDesc.DestBlend = D3D12_BLEND_ONE;
      renderTargetBlendDesc.BlendOp = renderTargetBlendDesc.BlendOpAlpha = (type == Additive ? D3D12_BLEND_OP_ADD : D3D12_BLEND_OP_REV_SUBTRACT);
      renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
      renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ONE;
      renderTargetBlendDesc.BlendOpAlpha = renderTargetBlendDesc.BlendOp;
      break;
    case BlendType::AlphaBlend:
      renderTargetBlendDesc.BlendEnable = true;
      renderTargetBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
      renderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
      renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
      renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
      renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_DEST_ALPHA;
      renderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
      break;
    default:
      throw std::exception("Unknown blend state!");
    }
  }
}