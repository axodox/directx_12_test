#pragma once
#include "BitwiseOperations.h"

namespace dx12test::Graphics
{
  struct GraphicsData
  {
    virtual uint8_t* Data() const = 0;
    virtual size_t Length() const = 0;    
    virtual ~GraphicsData() = default;

    virtual D3D12_RESOURCE_DESC GetDesc() const = 0;
  };

  struct BufferData : GraphicsData
  {
    virtual D3D12_RESOURCE_DESC GetDesc() const override
    {
      D3D12_RESOURCE_DESC result;
      BitwiseOperations::zero_memory(result);
      result.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
      result.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
      result.Width = Length();
      result.Height = 1;
      result.DepthOrArraySize = 1;
      result.MipLevels = 1;
      result.Format = DXGI_FORMAT_UNKNOWN;
      result.SampleDesc.Count = 1;
      result.SampleDesc.Quality = 0;
      result.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
      result.Flags = D3D12_RESOURCE_FLAG_NONE;
      return result;
    }
  };

  template<typename T>
  struct ArrayBufferData : BufferData
  {
    typedef T ItemType;
    std::vector<T> Buffer;

    virtual uint8_t* Data() const override
    {
      return reinterpret_cast<uint8_t*>(Buffer.data());
    }

    virtual size_t Length() const override
    {
      return Buffer.size() * sizeof(T);
    }
  };

  template<typename T>
  struct ArrayBufferPlaceholder : BufferData
  {
    size_t Size;

    ArrayBufferPlaceholder(size_t size) :
      Size(size)
    { }

    virtual uint8_t* Data() const override
    {
      return nullptr;
    }

    virtual size_t Length() const override
    {
      return Size * sizeof(T);
    }
  };  
}