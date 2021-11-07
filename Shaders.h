#pragma once
#include "pch.h"

namespace dx12test::Graphics
{
  enum class ShaderType
  {
    Vertex,
    Hull,
    Domain,
    Geometry,
    Pixel,
    Compute
  };

  class ShaderBase
  {
    friend class PipelineStateFactory;

  public:
    ShaderBase(const std::filesystem::path& path);
    virtual ~ShaderBase() = default;

    virtual ShaderType Type() const = 0;

  private:
    D3D12_SHADER_BYTECODE ByteCode() const;

    std::vector<uint8_t> _bytecode;
  };

  template<ShaderType CType>
  class TypedShader : public ShaderBase
  {
    using ShaderBase::ShaderBase;

    virtual ShaderType Type() const override
    {
      return CType;
    }
  };

  typedef TypedShader<ShaderType::Vertex> VertexShader;
  typedef TypedShader<ShaderType::Hull> HullShader;
  typedef TypedShader<ShaderType::Domain> DomainShader;
  typedef TypedShader<ShaderType::Geometry> GeometryShader;
  typedef TypedShader<ShaderType::Pixel> PixelShader;
  typedef TypedShader<ShaderType::Compute> ComputeShader;

  extern template VertexShader;
  extern template HullShader;
  extern template DomainShader;
  extern template GeometryShader;
  extern template PixelShader;
  extern template ComputeShader;
}