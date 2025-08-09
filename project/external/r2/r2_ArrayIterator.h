//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.11.15 PM.00.19
// # Version			: 1.0.0
//

#pragma once

#include "r2_Assert.h"
#include "r2_RemovePointer.h"

namespace r2
{
	template<typename T, int64_t ARRAY_SIZE>
	class ArrayIterator
	{
	public:
		static_assert( ARRAY_SIZE > 0 );



		using ValueT = r2::RemovePointer_T<T>;
		using IndexT = int64_t;



		ArrayIterator() : mArray( nullptr ), mIndex( 0 )
		{}
		explicit ArrayIterator( ValueT* const array_ptr ) : mArray( array_ptr ), mIndex( 0 )
		{}
		explicit ArrayIterator( ValueT* const array_ptr, const IndexT index ) : mArray( array_ptr ), mIndex( index )
		{}



		ArrayIterator& operator++()
		{
			++mIndex;
			return ( *this );
		}
		ArrayIterator& operator--()
		{
			--mIndex;
			return ( *this );
		}



		bool operator==( const ArrayIterator& other ) const
		{
			return ( other.mArray == mArray ) && ( other.mIndex == mIndex );
		}
		bool operator!=( const ArrayIterator& other ) const
		{
			return !operator==( other );
		}



		ValueT& operator*() const
		{
			return ( *( operator->() ) );
		}
		ValueT* operator->() const
		{
			R2ASSERT( nullptr != mArray, "" );
			R2ASSERT( ARRAY_SIZE > mIndex, "" );

			return ( mArray + mIndex );
		}



		ValueT* mArray;
		IndexT mIndex;
	};



	template<typename T, int64_t ARRAY_SIZE>
	class ConstArrayIterator
	{
	public:
		static_assert( ARRAY_SIZE > 0 );



		using ValueT = r2::RemovePointer_T<T>;
		using IndexT = int64_t;



		ConstArrayIterator() : mArray( nullptr ), mIndex( 0 )
		{}
		explicit ConstArrayIterator( const ValueT* array_ptr ) : mArray( array_ptr ), mIndex( 0 )
		{}
		explicit ConstArrayIterator( const ValueT* array_ptr, const IndexT index ) : mArray( array_ptr ), mIndex( index )
		{}



		ConstArrayIterator& operator++()
		{
			++mIndex;
			return ( *this );
		}
		ConstArrayIterator& operator--()
		{
			--mIndex;
			return ( *this );
		}



		bool operator==( const ConstArrayIterator& other ) const
		{
			return ( other.mArray == mArray ) && ( other.mIndex == mIndex );
		}
		bool operator!=( const ConstArrayIterator& other ) const
		{
			return !operator==( other );
		}



		const ValueT& operator*() const
		{
			return ( *( operator->() ) );
		}
		const ValueT* operator->() const
		{
			R2ASSERT( nullptr != mArray, "" );
			R2ASSERT( ARRAY_SIZE > mIndex, "" );

			return ( mArray + mIndex );
		}



		const ValueT* mArray;
		IndexT mIndex;
	};
}