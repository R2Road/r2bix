#include "r2_task_queue.hpp"

#include "r2_assert.hpp"

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