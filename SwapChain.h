#pragma once
#include "GraphicsResource.h"

namespace dx12test::Graphics
{
  class SwapChainBase : public GraphicsResource
  {
  public:
    void Resize();
    void Present();
    bool IsLost() const;

    virtual ~SwapChainBase() = default;

  protected:
    winrt::com_ptr<IDXGISwapChain> _swapChain;
    D3D12_VIEWPORT _viewport;
    uint8_t _sampleCount;
    bool _isLost = false;

    SwapChainBase(
      const winrt::com_ptr<ID3D12DeviceT>& device, 
      uint8_t sampleCount);
    void PrepareBackBuffer();    

    virtual DirectX::XMUINT2 GetSize() const = 0;
    virtual DXGI_MATRIX_3X2_F GetTransform() const = 0;
  };

  class SwapChainPanel : public SwapChainBase
  {
    static const uint32_t _minBufferSize = 64u;

  public:
    SwapChainPanel(
      const winrt::com_ptr<ID3D12CommandQueue>& directQueue,
      const winrt::Windows::UI::Xaml::Controls::SwapChainPanel& swapChainPanel, 
      uint8_t sampleCount = 1);

  private:
    winrt::Windows::UI::Xaml::Controls::SwapChainPanel _panel;

    virtual DirectX::XMUINT2 GetSize() const override;
    virtual DXGI_MATRIX_3X2_F GetTransform() const override;
  };
}