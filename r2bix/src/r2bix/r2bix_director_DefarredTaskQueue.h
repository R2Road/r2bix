#pragma once

#include "r2_TaskQueue.h"

namespace r2bix_director
{
	class DefarredTaskQueue
	{
	private:
		enum { TaskQueueCount = 2 };



	public:
		DefarredTaskQueue();

		

		void Process();
		void Swap();



	private:
		r2::TaskQueue mQueueList[TaskQueueCount];
		int mCurrentQueueIndex;
	};
}