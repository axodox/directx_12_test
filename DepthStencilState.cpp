#include "pch.h"
#include "DepthStencilState.h"
#include "BitwiseOperations.h"

using namespace dx12test::BitwiseOperations;

namespace dx12test::Graphics
{
  constexpr DepthStencilState::DepthStencilState(bool depthWrite, ComparisonFunction depthFunc)
  {
    _description.DepthEnable = true;
    _description.DepthWriteMask = depthWrite ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
    _description.DepthFunc = D3D12_COMPARISON_FUNC(depthFunc);
    
    _description.StencilEnable = false;
    _description.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
    _description.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

    const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp{ 
      D3D12_STENCIL_OP_KEEP, 
      D3D12_STENCIL_OP_KEEP, 
      D3D12_STENCIL_OP_KEEP, 
      D3D12_COMPARISON_FUNC_ALWAYS 
    };
    _description.FrontFace = defaultStencilOp;
    _description.BackFace = defaultStencilOp;
  }

  const DepthStencilState DepthStencilState::Default = {};
}