#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "ResourceHeapBuilder.h"
#include "VertexPosition.h"

using namespace dx12test::Graphics;
using namespace DirectX;

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::directx_12_test::implementation
{
  MainPage::MainPage()
  {
    InitializeComponent();

    _device = make_unique<GraphicsDevice>();
    _swapChain = make_unique<SwapChainPanel>(_device->DirectQueue(), RenderPanel());
    
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
