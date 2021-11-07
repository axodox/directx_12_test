#include "pch.h"
#include "FileAccess.h"

namespace dx12test::Storage
{
  std::vector<uint8_t> load_file(const std::filesystem::path& path)
  {
    FILE* file = nullptr;
    _wfopen_s(&file, path.c_str(), L"rb");
    fseek(file, 0, SEEK_END);
    auto length = ftell(file);

    std::vector<uint8_t> buffer(length);

    fseek(file, 0, SEEK_SET);
    fread_s(buffer.data(), length, length, 1, file);
    fclose(file);

    return buffer;
  }
}