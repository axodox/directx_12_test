#include "pch.h"
#include "SwapChain.h"
#include "WinUiThreading.h"

using namespace dx12test::Threading;
using namespace DirectX;
using namespace std;
using namespace winrt;

namespace dx12test::Graphics
{
  void SwapChainBase::Resize()
  {
    auto size = GetSize();
    check_hresult(_swapChain->ResizeBuffers(2, size.x, size.y, DXGI_FORMAT_UNKNOWN, 0));
    PrepareBackBuffer();
  }

  void SwapChainBase::Present()
  {
    if (_sampleCount > 1)
    {
      //TBD
    }

    auto result = _swapChain->Present(1, 0);
    switch (result)
    {
    case DXGI_ERROR_DEVICE_HUNG:
    case DXGI_ERROR_DEVICE_REMOVED:
    case DXGI_ERROR_DEVICE_RESET:
    case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
    case DXGI_ERROR_INVALID_CALL: //Restart app
      _isLost = true;
      winrt::Windows::ApplicationModel::Core::CoreApplication::Exit();
      break;
    default:
      winrt::check_hresult(result);
      break;
    }
  }

  bool SwapChainBase::IsLost() const
  {
    return _isLost;
  }

  SwapChainBase::SwapChainBase(
    const com_ptr<ID3D12DeviceT>& device,
    uint8_t sampleCount)
  {
    _device = device;
    _sampleCount = sampleCount; 
    _viewport.MaxDepth = D3D12_MAX_DEPTH;
    _viewport.MinDepth = D3D12_MIN_DEPTH;
  }

  void SwapChainBase::PrepareBackBuffer()
  {
    //TBD
  }

  SwapChainPanel::SwapChainPanel(
    const winrt::com_ptr<ID3D12CommandQueue>& directQueue,
    const winrt::Windows::UI::Xaml::Controls::SwapChainPanel& swapChainPanel, 
    uint8_t sampleCount) :
    SwapChainBase(device_of(directQueue), sampleCount),
    _panel(swapChainPanel)
  {
    com_ptr<IDXGIFactoryT> dxgiFactory;
    check_hresult(CreateDXGIFactory1(guid_of<IDXGIFactoryT>(), dxgiFactory.put_void()));

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

    auto size = GetSize();
    swapChainDesc.Width = size.x;
    swapChainDesc.Height = size.y;

    com_ptr<IDXGISwapChain1> swapChain1;
    check_hresult(dxgiFactory->CreateSwapChainForComposition(
      directQueue.get(),
      &swapChainDesc,
      nullptr,
      swapChain1.put()
    ));
    _swapChain = swapChain1.as<IDXGISwapChain>();

    auto swapChain2 = _swapChain.as<IDXGISwapChain2>();
    auto swapChainTransform = GetTransform();
    check_hresult(swapChain2->SetMatrixTransform(&swapChainTransform));

    auto nativePanel = swapChainPanel.as<ISwapChainPanelNative>();
    nativePanel->SetSwapChain(_swapChain.get());

    PrepareBackBuffer();
  }

  DirectX::XMUINT2 SwapChainPanel::GetSize() const
  {
    return send_or_post<XMUINT2>(_panel.Dispatcher(), [&] {
      return XMUINT2(
        max((uint32_t)(_panel.ActualWidth() * _panel.CompositionScaleX()), _minBufferSize),
        max((uint32_t)(_panel.ActualHeight() * _panel.CompositionScaleY()), _minBufferSize));
      });
  }

  DXGI_MATRIX_3X2_F SwapChainPanel::GetTransform() const
  {
    return send_or_post<DXGI_MATRIX_3X2_F>(_panel.Dispatcher(), [&] {
      DXGI_MATRIX_3X2_F transformation{};
      transformation._11 = 1.0f / _panel.CompositionScaleX();
      transformation._22 = 1.0f / _panel.CompositionScaleY();
      return transformation;
      });
  }
}