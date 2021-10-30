#pragma once
#include "MainPage.g.h"

#include "GraphicsDevice.h"
#include "SwapChain.h"

namespace winrt::directx_12_test::implementation
{
  struct MainPage : MainPageT<MainPage>
  {
    MainPage();

    int32_t MyProperty();
    void MyProperty(int32_t value);

    void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);

  private:
    std::unique_ptr<dx12test::Graphics::GraphicsDevice> _device;
    std::unique_ptr<dx12test::Graphics::SwapChainBase> _swapChain;
  };
}

namespace winrt::directx_12_test::factory_implementation
{
  struct MainPage : MainPageT<MainPage, implementation::MainPage>
  {
  };
}
