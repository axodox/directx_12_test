#pragma once
#include "GraphicsResource.h"

namespace dx12test::Graphics
{
  class GraphicsDevice : public GraphicsResource
  {
  public:
    GraphicsDevice();

    const winrt::com_ptr<ID3D12CommandQueue>& DirectQueue() const;
    const winrt::com_ptr<ID3D12CommandQueue>& CopyQueue() const;

  private:
    winrt::com_ptr<ID3D12CommandQueue> _directQueue;
    winrt::com_ptr<ID3D12CommandQueue> _copyQueue;
  };
}