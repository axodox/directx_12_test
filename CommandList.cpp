#include "pch.h"
#include "CommandList.h"

using namespace winrt;

namespace dx12test::Graphics
{
  void CommandAllocator::AddRef()
  {
    _refCount++;
  }

  void CommandAllocator::Release()
  {
    if (--_refCount == 0)
    {
      check_hresult(Resource->Reset());
    }
  }
}