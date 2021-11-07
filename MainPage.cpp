#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "ResourceHeapBuilder.h"
#include "ResourceDescriptorHeap.h"
#include "VertexPosition.h"
#include "RootSignature.h"

using namespace dx12test::Graphics;
using namespace DirectX;

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::directx_12_test::implementation
{
  struct MyRootSignature : public RootSignatureBase
  {
    ConstantBufferViewParameter Contants;
    ShaderResourceViewParameter MainTexture;

    MyRootSignature(RootSignatureInitializationContext& context) :
      RootSignatureBase(context),
      Contants(this, 0),
      MainTexture(this, 0)
    { }
  };

  MainPage::MainPage()
  {
    InitializeComponent();

    _device = make_unique<GraphicsDevice>();
    _swapChain = make_unique<SwapChainPanel>(_device->DirectQueue(), RenderPanel());
    
    RootSignatureFactory rootSignatureFactory{ _device->Device() };
    auto signature = rootSignatureFactory.Create<MyRootSignature>();

    ResourceHeapBuilder builder{ResourceCategory::Buffers, _device->CopyQueue()};

    IndexData<uint16_t> indices{{ 1, 2, 3 }};
    VertexData<VertexPosition> vertices{{ 
        XMFLOAT3{0,0,0},
        XMFLOAT3{0,1,0},
        XMFLOAT3{0,0,2}
      }};

    struct MyConstants
    {
      XMFLOAT4X4 WorldViewProjection;
    };
    ConstantPlaceholder<MyConstants> constants;
    
    auto ib = builder.AddIndexBuffer(indices);
    auto vb = builder.AddVertexBuffer(vertices);
    auto cb = builder.AddConstantBuffer(constants);
    auto heap = builder.Build();

    ResourceDescriptorHeap resourceDescHeap{_device->Device()};
    auto cbv = resourceDescHeap.AddConstantBufferView(move(cb));
    resourceDescHeap.Rebuild();
  }

  int32_t MainPage::MyProperty()
  {
    throw hresult_not_implemented();
  }

  void MainPage::MyProperty(int32_t /* value */)
  {
    throw hresult_not_implemented();
  }

  void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
  {
    myButton().Content(box_value(L"Clicked"));
  }
}
