#pragma once
#include "ResourceHeapItem.h"
#include "GraphicsData.h"
#include "GraphicsResource.h"

namespace dx12test::Graphics
{
  class ResourceUpdater : public GraphicsResource
  {
    struct ResourceUpdate
    {
      ResourceHeapItem* HeapItem; 
      const GraphicsData* Data;
    };

  public:
    ResourceUpdater(const winrt::com_ptr<ID3D12CommandQueue>& copyQueue);

    void ScheduleUpdate(ResourceHeapItem* heapItem, const GraphicsData* data);
    void ExecuteUpdates();

  private:
    winrt::com_ptr<ID3D12CommandQueue> _copyQueue;
    winrt::com_ptr<ID3D12HeapT> _stagingHeap;
    std::vector<ResourceUpdate> _updates;
  };
}