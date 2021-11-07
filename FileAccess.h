#pragma once
#include "pch.h"

namespace dx12test::Storage
{
  std::vector<uint8_t> load_file(const std::filesystem::path& path);
}