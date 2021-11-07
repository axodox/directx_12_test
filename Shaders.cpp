#include "pch.h"
#include "Shaders.h"
#include "FileAccess.h"

using namespace dx12test::Storage;

namespace dx12test::Graphics
{
  ShaderBase::ShaderBase(const std::filesystem::path& path) :
    _bytecode(load_file(path))
  { }

  template VertexShader;
  template HullShader;
  template DomainShader;
  template GeometryShader;
  template PixelShader;
  template ComputeShader;
}