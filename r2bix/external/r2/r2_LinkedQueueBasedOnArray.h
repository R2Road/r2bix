//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.05.07 AM.08.18
// # Version			: 1.0.0
//

#pragma once

#include "r2_Node4ListAllocatorBasedOnArray.h"
#include "r2_Node4ListIterator.h"

#include "r2_Assert.h"

namespace r2
{
	//
	// # Warning
	//
	// ValueT 로 std::shared_ptr 등을 사용하고 있다면 NodeCleaner 를 ListNodeCleaner_ClearValue 로 설정.
	//

	template<typename T, uint32_t N, typename NodeCleaner = Node4ListCleaner_StayValue<T>>
	class LinkedQueueBasedOnArray
	{
	public:
		using ValueT = T;
		using SizeT = uint32_t;

		using NodeT = Node4List<ValueT>;
		using AllocatorT = Node4ListAllocatorBasedOnArray<ValueT, N + 1u, NodeCleaner>; // N + Head

		using IteratorT = Node4ListIterator<ValueT>;
		using ConstIteratorT = Node4ListConstIterator<ValueT>;
		using ReverseIteratorT = Node4ListReverseIterator<ValueT>;
		using ConstReverseIteratorT = Node4ListConstReverseIterator<ValueT>;



		LinkedQueueBasedOnArray() : mAllocator(), mEndNode( nullptr ), mSize( 0u )
		{
			Clear();
		}



		//
		// Iteration
		//
		IteratorT begin()
		{
			return IteratorT( mEndNode->pNext );
		}
		IteratorT end()
		{
			return IteratorT( mEndNode );
		}
		ConstIteratorT begin() const
		{
			return ConstIteratorT( mEndNode->pNext );
		}
		ConstIteratorT end() const
		{
			return ConstIteratorT( mEndNode );
		}

		ReverseIteratorT rbegin()
		{
			return ReverseIteratorT( mEndNode->pPrev );
		}
		ReverseIteratorT rend()
		{
			return ReverseIteratorT( mEndNode );
		}
		ConstReverseIteratorT rbegin() const
		{
			return ConstReverseIteratorT( mEndNode->pPrev );
		}
		ConstReverseIteratorT rend() const
		{
			return ConstReverseIteratorT( mEndNode );
		}



		void Clear()
		{
			//
			// Clear
			//
			mAllocator.Clear();

			//
			// End
			//
			mEndNode = mAllocator.Pop();
			mEndNode->pPrev = mEndNode;
			mEndNode->pNext = mEndNode;

			mSize = 0u;
		}



	public:
		SizeT Size() const
		{
			return mSize;
		}
		bool Empty() const
		{
			return ( 0u == mSize );
		}
		SizeT Capacity() const
		{
			return mAllocator.Capacity();
		}
		SizeT GetRemainSpaceSize() const
		{
			return mAllocator.Size();
		}



		//
		// Push Back
		//
		void Push( const ValueT& new_value )
		{
			if( mAllocator.Empty() )
			{
				return;
			}

			auto new_back_node = mAllocator.Pop();
			new_back_node->MyValue = new_value;

			// Prev
			mEndNode->pPrev->pNext = new_back_node;

			// New
			new_back_node->pPrev = mEndNode->pPrev;
			new_back_node->pNext = mEndNode;

			// Next
			mEndNode->pPrev = new_back_node;

			++mSize;
		}

		//
		// Pop Front
		//
		void Pop()
		{
			erase( mEndNode->pNext );
		}

	private:
		void erase( NodeT* target_node )
		{
			if( mEndNode == target_node )
			{
				return;
			}

			auto pPrev = target_node->pPrev;
			auto pNext = target_node->pNext;

			pPrev->pNext = pNext;
			pNext->pPrev = pPrev;

			--mSize;

			mAllocator.Push( target_node );
		}



	public:
		//
		// Get Value
		//
		const ValueT& Front() const
		{
			return mEndNode->pNext->MyValue;
		}
		const ValueT& Back() const
		{
			return mEndNode->pPrev->MyValue;
		}



	private:
		AllocatorT mAllocator;
		NodeT* mEndNode;
		SizeT mSize;
	};
}