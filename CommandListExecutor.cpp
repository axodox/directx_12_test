#include "pch.h"
#include "CommandListExecutor.h"

namespace dx12test::Graphics
{
  CommandListExecutor::CommandListExecutor(const std::shared_ptr<CommandAllocator>& commandAllocator, const std::shared_ptr<CommandList>& commandList) :
    GraphicsResource(device_of(commandAllocator->Resource)),
    _commandAllocator(commandAllocator),
    _commandList(commandList)
  { 
    _commandAllocator->AddRef();
    _commandList->State = CommandListState::Executing;
  }

  CommandListExecutor::~CommandListExecutor()
  {
    Reset();
  }

  bool CommandListExecutor::IsValid() const
  {
    return _commandAllocator && _commandList;
  }

  void CommandListExecutor::Reset()
  {
    if (_commandList)
    {
      _commandList->State = CommandListState::Idle;
      _commandList.reset();
    }

    if (_commandAllocator)
    {
      _commandAllocator->Release();
      _commandAllocator.reset();
    }
  }
}