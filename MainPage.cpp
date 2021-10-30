#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "ResourceHeapBuilder.h"

using namespace dx12test::Graphics;

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
    
    ResourceHeapBuilder builder{HeapContentKind::Buffers, _device->CopyQueue()};
    builder.AddIndexBuffer(ResourceUsageMode::Immutable,  make_shared<IndexPlaceholder<uint16_t>>(16));
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
