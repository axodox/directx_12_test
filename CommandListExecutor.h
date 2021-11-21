#pragma once
#include "CommandList.h"

namespace dx12test::Graphics
{
  class CommandListExecutor : public GraphicsResource
  {
  public:
    CommandListExecutor(const CommandListExecutor&) = delete;
    CommandListExecutor& operator=(const CommandListExecutor&) = delete;
    CommandListExecutor(CommandListExecutor&&) = default;
    CommandListExecutor& operator=(CommandListExecutor&&) = default;

    CommandListExecutor(const std::shared_ptr<CommandAllocator>& commandAllocator, const std::shared_ptr<CommandList>& commandList);
    ~CommandListExecutor();

    bool IsValid() const;
    void Reset();

  private:
    std::shared_ptr<CommandAllocator> _commandAllocator;
    std::shared_ptr<CommandList> _commandList;
  };
}