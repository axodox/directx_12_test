#pragma once
#include "pch.h"

namespace dx12test::Infrastructure
{
  struct value_container_base
  {
    virtual ~value_container_base() = default;
  };

  template<typename T>
  class value_container : public value_container_base
  {
    T value;
  };

  class value_bag
  {
  public:
    template<typename T>
    T& add();

  private:
    std::vector<std::unique_ptr<value_container_base>> _items;
  };

  template<typename T>
  inline T& value_bag::add()
  {
    auto item = std::make_unique<value_container<T>>();
    auto& result = item->value;
    _items.push_back(std::move(item));
    return result;
  }
}