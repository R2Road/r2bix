#include "r2_TaskQueue.h"

#include "r2_Assert.h"

namespace r2
{
	TaskQueue::TaskQueue() : mContainer()
	{}

	void TaskQueue::Add( const Task& task )
	{
		mContainer.push_back( task );
	}

	void TaskQueue::Process()
	{
		for( const auto& task : mContainer )
		{
			task();
		}

		mContainer.clear();
	}
}