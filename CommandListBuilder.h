#pragma once
#include "CommandList.h"
#include "CommandListExecutor.h"

namespace dx12test::Graphics
{
  class ResourceDescriptorHeap;

  class CommandListBuilder : public GraphicsResource
  {
  public:
    CommandListBuilder(const CommandListBuilder&) = delete;
    CommandListBuilder& operator=(const CommandListBuilder&) = delete;
    CommandListBuilder(CommandListBuilder&&) = default;
    CommandListBuilder& operator=(CommandListBuilder&&) = default;

    CommandListBuilder(const std::shared_ptr<CommandAllocator>& commandAllocator, const std::shared_ptr<CommandList>& commandList);
    ~CommandListBuilder();

    bool IsValid() const;
    void Reset();
    CommandListExecutor Build();

    void SetDescriptorHeaps(ResourceDescriptorHeap& resourceHeap);

    ID3D12GraphicsCommandListT* Resource() const;

  private:
    std::shared_ptr<CommandAllocator> _commandAllocator;
    std::shared_ptr<CommandList> _commandList;
  };
}