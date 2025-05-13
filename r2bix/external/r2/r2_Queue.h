#pragma once

#include <vector>

#include "r2_Assert.h"

namespace r2
{
	template<typename T, T Default_Value = 0u >
	class Queue
	{
	public:
		using ValueT  = T;
		using LinearT = std::size_t;
	private:
		using ContainerT = std::vector<int>;
		using ConstIteratorT = ContainerT::const_iterator;
		using IteratorT = ContainerT::iterator;



	public:
		Queue() : mContainer(), mHead( 0u ), mTail( 0u )
		{}



		//
		// Iteration
		//
		ConstIteratorT begin() const
		{
			return mContainer.begin();
		}
		ConstIteratorT end() const
		{
			return mContainer.end();
		}
		IteratorT begin()
		{
			return mContainer.begin();
		}
		IteratorT end()
		{
			return mContainer.end();
		}



		//
		// for Test
		//
		LinearT GetHead() const
		{
			return mHead;
		}
		LinearT GetTail() const
		{
			return mTail;
		}
		//
		//
		//
		bool Empty() const
		{
			return mHead == mTail;
		}
		const ContainerT& GetContainer() const
		{
			return mContainer;
		}



		void Reset()
		{
			for( auto cur = mContainer.begin(), end = mContainer.end(); end != cur; ++cur )
			{
				*cur = Default_Value;
			}
			mHead = 0u;
			mTail = 0u;
		}

		void Resize( const LinearT size )
		{
			mContainer.resize( size, Default_Value );
		}

		void Push( const ValueT new_value )
		{
			if( mTail >= mContainer.size() )
			{
				R2ASSERT( false, "" );
				return;
			}

			mContainer[mTail++] = new_value;
		}

		const ValueT Pop()
		{
			if( Empty() )
			{
				R2ASSERT( false, "" );
				return Default_Value;
			}

			return mContainer[mHead++];
		}



	private:
		ContainerT mContainer;
		LinearT mHead;
		LinearT mTail;
	};
}