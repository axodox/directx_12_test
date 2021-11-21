#include "pch.h"
#include "CommandListPool.h"

using namespace std;
using namespace winrt;

namespace dx12test::Graphics
{
  CommandListPool::CommandListPool(const winrt::com_ptr<ID3D12DeviceT>& device, CommandListType type) :
    GraphicsResource(device),
    _type(type)
  { }

  CommandListBuilder CommandListPool::CreateBuilder(const PipelineState & initialState)
  {
    lock_guard lock(_mutex);

    auto allocator = FindOrCreateIdleAllocator();

    auto commandList = FindIdleCommandList();    
    if (!commandList)
    {
      commandList = CreateCommandList(allocator.get(), initialState);
    }
    else
    {
      commandList->Resource->Reset(allocator->Resource.get(), initialState._state.get());
    }

    return CommandListBuilder(allocator, commandList);
  }

  std::shared_ptr<CommandAllocator> CommandListPool::FindOrCreateIdleAllocator()
  {
    //Find idle allocator and return if any
    for (auto& allocator : _allocators)
    {
      if (!allocator->IsBusy) return allocator;
    }

    //Otherwise create and store new allocator
    auto allocator = make_shared<CommandAllocator>();
    check_hresult(_device->CreateCommandAllocator(
      D3D12_COMMAND_LIST_TYPE(_type),
      guid_of<ID3D12CommandAllocator>(),
      allocator->Resource.put_void()));
    _allocators.push_back(allocator);

    return allocator;
  }

  std::shared_ptr<CommandList> CommandListPool::FindIdleCommandList()
  {
    for (auto& commandList : _commandLists)
    {
      if (commandList->State == CommandListState::Idle) return commandList;
    }

    return nullptr;
  }
  
  std::shared_ptr<CommandList> CommandListPool::CreateCommandList(CommandAllocator* allocator, const PipelineState& initialState)
  {
    com_ptr<ID3D12GraphicsCommandListT> commandList;
    check_hresult(_device->CreateCommandList(
      0,
      D3D12_COMMAND_LIST_TYPE(_type),
      allocator->Resource.get(),
      initialState._state.get(),
      guid_of<ID3D12GraphicsCommandListT>(),
      commandList.put_void()));

    auto result = make_shared<CommandList>();
    result->Resource = move(commandList);
    _commandLists.push_back(result);
    return result;
  }
}