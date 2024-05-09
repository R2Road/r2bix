#include "r2bix_director_DefarredTaskQueue.h"

namespace r2bix_director
{
	DefarredTaskQueue::DefarredTaskQueue() : mQueueList(), mCurrentQueueIndex( 0 )
	{}


	void DefarredTaskQueue::Process()
	{
		//
		// ������ ��� Task�� ���� �� �� ���� ó���� �ݺ��Ѵ�.
		//

		r2::TaskQueue* target_queue = nullptr;

		do
		{

			//
			// ���� Q�� ���� �����Ѵ�.
			//
			target_queue = &mQueueList[mCurrentQueueIndex];

			//
			// Task ó�� �������� �� Task�� ������ �� �ִ�.
			// ���� Q �� �������� �ʵ��� �̸� Swap �Ѵ�.
			//
			Swap();

			//
			// ó��
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