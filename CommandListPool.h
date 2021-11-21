#pragma once
#include "GraphicsResource.h"
#include "CommandListBuilder.h"

namespace dx12test::Graphics
{
  class CommandListPool : public GraphicsResource
  {
  public:
    CommandListPool(const winrt::com_ptr<ID3D12DeviceT>& device, CommandListType type);

    CommandListBuilder CreateBuilder(const PipelineState& initialState);

  private:
    std::mutex _mutex;
    CommandListType _type;
    std::vector<std::shared_ptr<CommandAllocator>> _allocators;
    std::vector<std::shared_ptr<CommandList>> _commandLists;

    std::shared_ptr<CommandAllocator> FindOrCreateIdleAllocator();
    std::shared_ptr<CommandList> FindIdleCommandList();
    std::shared_ptr<CommandList> CreateCommandList(CommandAllocator* allocator, const PipelineState& initialState);
  };
}