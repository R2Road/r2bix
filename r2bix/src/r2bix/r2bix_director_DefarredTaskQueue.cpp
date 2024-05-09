#include "r2bix_director_DefarredTaskQueue.h"

namespace r2bix_director
{
	DefarredTaskQueue::DefarredTaskQueue() : mQueueList(), mCurrentQueueIndex( 0 )
	{}


	void DefarredTaskQueue::Swap()
	{
		//
		// Update Index
		//
		++mCurrentQueueIndex;
		if( TaskQueueCount <= mCurrentQueueIndex )
		{
			mCurrentQueueIndex = 0;
		}
	}
}