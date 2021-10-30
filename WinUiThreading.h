#pragma once
#include "pch.h"

namespace dx12test::Threading
{
  template <typename TResult>
  TResult send_or_post(winrt::Windows::UI::Core::CoreDispatcher const& dispatcher, std::function<TResult()> action)
  {
    if constexpr (std::is_same<void, TResult>::value)
    {
      if (dispatcher.HasThreadAccess())
      {
        action();
      }
      else
      {
        dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [action]() {
          action();
          }).get();
      }
    }
    else
    {
      TResult result;
      if (dispatcher.HasThreadAccess())
      {
        result = action();
      }
      else
      {
        dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [action, &result]() {
          result = action();
          }).get();
      }
      return result;
    }
  }
}