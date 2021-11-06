#pragma once
#include "pch.h"

namespace dx12test::BitwiseOperations
{
  template<typename T>
  inline constexpr T bitwise_negate(const T a)
  {
    return (T)(~static_cast<std::underlying_type_t<T>>(a));
  }

  template<
    typename T,
    typename U,
    typename V = std::underlying_type_t<T>,
    typename = std::enable_if<std::is_same<std::underlying_type_t<T>, std::underlying_type_t<U>>::value>>
    inline constexpr V bitwise_or(const T a, const U b)
  {
    return (V)(static_cast<V>(a) | static_cast<V>(b));
  }

  template<typename T>
  inline constexpr T bitwise_xor(const T a, const T b)
  {
    return (T)(static_cast<std::underlying_type_t<T>>(a) ^ static_cast<std::underlying_type_t<T>>(b));
  }

  template<typename T>
  inline constexpr T bitwise_or(const T a, const T b)
  {
    return (T)(static_cast<std::underlying_type_t<T>>(a) | static_cast<std::underlying_type_t<T>>(b));
  }

  template<typename THead, typename... TTail, class = std::enable_if_t<std::conjunction<std::is_same<THead, TTail>...>::value, void>>
  inline constexpr THead bitwise_or(const THead head, const TTail ... tail)
  {
    return (THead)(static_cast<std::underlying_type_t<THead>>(head) | ... | static_cast<std::underlying_type_t<TTail>>(tail));
  }

  template<typename T>
  inline constexpr T bitwise_and(const T a, const T b)
  {
    return (T)(static_cast<std::underlying_type_t<T>>(a) & static_cast<std::underlying_type_t<T>>(b));
  }

  template<typename T>
  inline constexpr bool has_flag(const T a, const T b)
  {
    return bitwise_and(a, b) == b;
  }

  template<typename T>
  inline constexpr bool has_any_flag(const T a, const T b)
  {
    return bitwise_and(a, b) != (T)0;
  }

  template<typename T>
  inline void set_flag(T& a, const T b, const bool value)
  {
    if (value)
    {
      a = bitwise_or(a, b);
    }
    else
    {
      a = bitwise_and(a, bitwise_negate(b));
    }
  }

  template <typename TTarget, typename TSource>
  const TTarget& get_as(const TSource& source)
  {
    static_assert(sizeof(TTarget) == sizeof(TSource), "The size of target and source must be the same!");
    //static_assert(is_pod<TTarget>::value, "The target type must be plain old data!");

    return reinterpret_cast<const TTarget&>(source);
  }

  template <typename TTarget, typename TSource>
  void store_as(TTarget& target, const TSource& source)
  {
    target = get_as<TTarget>(source);
  }

  template<typename U, typename V>
  inline constexpr bool are_equal(const U& a, const V& b)
  {
    static_assert(std::is_trivially_copyable<U>::value && std::is_trivially_copyable<V>::value && sizeof(U) == sizeof(V));
    return memcmp(&a, &b, sizeof(U)) == 0;
  }

  template <typename T, size_t C>
  bool are_equal(const std::array<T, C>& a, const std::array<T, C>& b)
  {
    static_assert(std::is_trivially_copyable<T>::value);
    return memcmp(a.data(), b.data(), sizeof(T) * C) == 0;
  }

  template <typename T>
  bool are_equal(const T& a, const T& b)
  {
    static_assert(std::is_trivially_copyable<T>::value);
    return memcmp(&a, &b, sizeof(T)) == 0;
  }

  template <>
  inline bool are_equal<std::string>(const std::string& a, const std::string& b)
  {
    return a.compare(b) == 0;
  }

  template <>
  inline bool are_equal<std::wstring>(const std::wstring& a, const std::wstring& b)
  {
    return a.compare(b) == 0;
  }

  template <typename T>
  bool are_equal(const std::vector<T>& a, const std::vector<T>& b)
  {
    static_assert(std::is_trivially_copyable<T>::value);

    if (a.size() != b.size()) return false;
    return memcmp(a.data(), b.data(), sizeof(T) * a.size()) == 0;
  }

  template <typename T>
  constexpr T get_default()
  {
    T value;
    memset(&value, 0, sizeof(T));
    return value;
  }

  template <typename T>
  bool is_default(const T& value)
  {
    return are_equal<T>(value, T{});
  }

  template <typename T, typename U>
  T rotate(T value, U bits)
  {
    if constexpr (std::is_same<T, uint64_t>::value)
    {
      return _rotl64(value, (int)bits);
    }
    else if constexpr (std::is_same<T, uint32_t>::value)
    {
      return _rotl(value, (int)bits);
    }
    else
    {
      static_assert(false, "Rotate is not supported for this type.");
    }
  }

  template<typename T>
  void zero_memory(T& value)
  {
    memset(&value, 0, sizeof(T));
  }

  inline constexpr size_t align_size(size_t baseSize, size_t alignment)
  {
    auto mod = baseSize % alignment;
    return (mod == 0 ? baseSize : baseSize + alignment - mod);
  }
}