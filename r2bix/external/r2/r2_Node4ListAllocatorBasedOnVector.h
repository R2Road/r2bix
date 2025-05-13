//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.05.07 AM.08.18
// # Version			: 1.0.0
//

#pragma once

#include <vector>

#include "r2_Node4List.h"
#include "r2_Assert.h"

namespace r2
{
	//
	// # Warning
	//
	// ValueT �� std::shared_ptr ���� ����ϰ� �ִٸ� Cleaner �� ClearValue �� ����.
	//

	template<typename T, typename NodeCleaner = Node4ListCleaner_StayValue<T>>
	class Node4ListAllocatorBasedOnVector
	{
	public:
		using ValueT = T;
		using SizeT = uint32_t;

		using NodeT = Node4List<ValueT>;
		using ContainerT = std::vector<NodeT>;



		Node4ListAllocatorBasedOnVector() : mContainer(), mNodeCleaner(), mHead( nullptr ), mSize( 0u )
		{
			Clear();
		}
		explicit Node4ListAllocatorBasedOnVector( const SizeT size ) : mContainer(), mNodeCleaner(), mHead( nullptr ), mSize( 0u )
		{
			Reset( size );
		}



		//
		//
		//
		SizeT Size() const
		{
			return mSize;
		}
		SizeT Capacity() const
		{
			return static_cast<SizeT>( mContainer.size() );
		}
		bool Empty() const
		{
			return ( 0u == mSize );
		}



		//
		//
		//
		void Reset( const SizeT size )
		{
			mContainer.clear();
			mContainer.resize( size );

			Clear();
		}
		void Clear()
		{
			if( mContainer.empty() )
			{
				return;
			}

			//
			// Cleanup
			//
			for( auto& n : mContainer )
			{
				mNodeCleaner( &n );
			}

			//
			// Build Chain
			//
			mHead = &( *mContainer.begin() );
			if( 1 < mContainer.size() )
			{
				auto current_node = mHead;

				auto cur = mContainer.begin();
				++cur;
				for( auto end = mContainer.end(); end != cur; ++cur )
				{
					cur->pPrev = current_node;
					current_node->pNext = &( *cur );

					current_node = current_node->pNext;
				}
			}
			mSize = static_cast<uint32_t>( mContainer.size() );
		}



		//
		//
		//
		NodeT* Pop()
		{
			R2ASSERT( nullptr != mHead, "Empty : Node4ListAllocatorBasedOnVector::Pop()" );

			NodeT* ret = mHead;

			if( nullptr != ret )
			{
				mHead = ret->pNext;
				--mSize;
			}

			return ret;
		}
		void Push( NodeT* rest_node )
		{
			//
			//
			//
			mNodeCleaner( rest_node );

			//
			//
			//
			if( nullptr == mHead )
			{
				mHead = rest_node;
			}
			else
			{
				rest_node->pNext = mHead;
				mHead = rest_node;
			}

			++mSize;
		}



	private:
		ContainerT mContainer;
		NodeCleaner mNodeCleaner;
		NodeT* mHead;
		SizeT mSize;
	};
}