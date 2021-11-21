#pragma once
#include "CommandList.h"
#include "CommandListExecutor.h"

namespace dx12test::Graphics
{
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

  private:
    std::shared_ptr<CommandAllocator> _commandAllocator;
    std::shared_ptr<CommandList> _commandList;
  };
}