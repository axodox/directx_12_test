#include "pch.h"
#include "CommandListBuilder.h"
#include "ResourceDescriptorHeap.h"

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
  
  void CommandListBuilder::SetDescriptorHeaps(ResourceDescriptorHeap& resourceHeap)
  {
    assert(IsValid());

    ID3D12DescriptorHeap* heaps[] = {
      resourceHeap._heap.get()
    };
    _commandList->Resource->SetDescriptorHeaps(1, heaps);
  }
  
  ID3D12GraphicsCommandListT* CommandListBuilder::Resource() const
  {
    assert(IsValid());
    return _commandList->Resource.get();
  }
}