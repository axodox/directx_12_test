#pragma once
#include "GraphicsResource.h"
#include "PipelineState.h"

namespace dx12test::Graphics
{
  enum class CommandListType : std::underlying_type_t<D3D12_COMMAND_LIST_TYPE>
  {
    Direct = D3D12_COMMAND_LIST_TYPE_DIRECT,
    Compute = D3D12_COMMAND_LIST_TYPE_COMPUTE,
    Copy = D3D12_COMMAND_LIST_TYPE_COPY
  };

  struct CommandAllocator
  {
    winrt::com_ptr<ID3D12CommandAllocator> Resource;
    bool IsBusy = false;

    void AddRef();
    void Release();

  private:
    std::atomic_uint32_t _refCount = 0;
  };

  enum class CommandListState
  {
    Idle,
    Recording,
    Executing
  };

  struct CommandList
  {
    winrt::com_ptr<ID3D12GraphicsCommandListT> Resource;
    CommandListState State = CommandListState::Idle;
  };
}