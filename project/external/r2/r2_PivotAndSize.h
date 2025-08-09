#pragma once

#include "r2_TypeTraits.h"

namespace r2
{
	template<class T>
	class PivotAndSize
	{
	public:
		static_assert(
			   r2::is_same_v<T, char>
			|| r2::is_same_v<T, unsigned char>
			
			|| r2::is_same_v<T, int>
			|| r2::is_same_v<T, unsigned int>

			|| r2::is_same_v<T, long long int>
			|| r2::is_same_v<T, unsigned long long int>

			|| r2::is_same_v<T, float>
			|| r2::is_same_v<T, double>
			, "r2::PivotAndSize - Not Allowed Type"
		);

		using ValueT = T;



		explicit PivotAndSize() : mPivot( 0 ), mSize( 0 )
		{}
		explicit PivotAndSize( const ValueT pivot ) : mPivot( pivot ), mSize( 0 )
		{}
		explicit PivotAndSize( const ValueT pivot, const ValueT count ) : mPivot( pivot ), mSize( count )
		{}



		//
		//
		//
		bool operator==( const PivotAndSize<ValueT>& other ) const
		{
			return ( mPivot == other.GetPivot() )
				&& ( mSize == other.GetSize() );
		}
		bool operator!=( const PivotAndSize<ValueT>& other ) const
		{
			return !operator==( other );
		}



		//
		//
		//
		bool IsValid() const
		{
			return ( 0 < mSize );
		}
		bool IsInvalid() const
		{
			return !IsValid();
		}



		//
		//
		//
		ValueT GetPivot() const
		{
			return mPivot;
		}
		ValueT GetSize() const
		{
			return mSize;
		}
		ValueT GetEnd() const
		{
			const ValueT temp = mPivot + mSize;

			return (
				  temp == 0 // for unsigned
				? mPivot
				: (
					  mPivot >= temp
					? mPivot
					: temp - static_cast<ValueT>( 1 )
				)
			);
		}



		//
		//
		//
		void Increase()
		{
			++mSize;
		}



	private:
		const ValueT mPivot;
		ValueT mSize;
	};
}