#pragma once

#include "r2_TaskQueue.h"

namespace r2bix_director
{
	class DefarredTaskQueue
	{
	private:
		enum { TaskQueueCount = 2 };
		using ContainerT = r2::TaskQueue;
	public:
		using TaskT = typename r2::TaskQueue::Task;
		using SizeT = typename r2::TaskQueue::SizeT;



	public:
		DefarredTaskQueue();

		

		void Process();
	private:
		void Swap();



	public:
		void Add( const TaskT& task );



		SizeT Size() const
		{
			return mQueueList[mCurrentQueueIndex].Size();
		}
		bool Empty() const
		{
			return mQueueList[mCurrentQueueIndex].Empty();
		}



	private:
		ContainerT mQueueList[TaskQueueCount];
		int mCurrentQueueIndex;
	};
}