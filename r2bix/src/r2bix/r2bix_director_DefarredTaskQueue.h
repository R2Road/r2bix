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
		DefarredTaskQueue();

		

		void Process();
		void Swap();



	private:
		ContainerT mQueueList[TaskQueueCount];
		int mCurrentQueueIndex;
	};
}