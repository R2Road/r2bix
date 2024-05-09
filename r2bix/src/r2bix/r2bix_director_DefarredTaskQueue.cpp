#include "r2bix_director_DefarredTaskQueue.h"

namespace r2bix_director
{
	DefarredTaskQueue::DefarredTaskQueue() : mQueueList(), mCurrentQueueIndex( 0 )
	{}


	void DefarredTaskQueue::Process()
	{
		//
		// 보유한 모든 Task가 제거 될 때 까지 처리를 반복한다.
		//

		r2::TaskQueue* target_queue = nullptr;

		do
		{

			//
			// 현재 Q를 먼저 저장한다.
			//
			target_queue = &mQueueList[mCurrentQueueIndex];

			//
			// Task 처리 과정에서 새 Task가 생성될 수 있다.
			// 현재 Q 에 간섭하지 않도록 미리 Swap 한다.
			//
			Swap();

			//
			// 처리
			//
			target_queue->Process();

		} while( !mQueueList[mCurrentQueueIndex].Empty() );
	}
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