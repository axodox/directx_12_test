#include "pch.h"
#include "CommandListBuilder.h"

using namespace std;
using namespace winrt;

namespace dx12test::Graphics
{
  CommandListBuilder::CommandListBuilder(const std::shared_ptr<CommandAllocator>& commandAllocator, const std::shared_ptr<CommandList>& commandList) :
    GraphicsResource(device_of(commandAllocator->Resource)),
    _commandAllocator(commandAllocator),
    _commandList(commandList)
  {
    _commandAllocator->AddRef();
    _commandAllocator->IsBusy = true;
    _commandList->State = CommandListState::Recording;
  }

  CommandListBuilder::~CommandListBuilder()
  {
    Reset();
  }
  
  bool CommandListBuilder::IsValid() const
  {
    return _commandAllocator && _commandList;
  }

  void CommandListBuilder::Reset()
  {
    if (_commandList)
    {
      check_hresult(_commandList->Resource->Close());
      if (_commandList->State == CommandListState::Recording)
      {
        _commandList->State = CommandListState::Idle;
      }
      _commandList.reset();
    }

    if (_commandAllocator)
    {
      _commandAllocator->Release();
      _commandAllocator->IsBusy = false;
      _commandAllocator.reset();
    }
  }

  CommandListExecutor CommandListBuilder::Build()
  {
    CommandListExecutor result{ _commandAllocator, _commandList };
    Reset();
    return result;
  }
}