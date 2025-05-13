//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.06.17 AM.00.12
// # Version			: 1.0.1
//

#pragma once

#include "r2_TypeTraits.h"

namespace r2
{
	template<class T>
	class Range
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
			, "r2::Range - Not Allowed Type"
		);

		using ValueT = T;
		using MyT = Range<T>;



		explicit Range() : mStart( 0 ), mEnd( 0 )
		{}
		explicit Range( const ValueT start, const ValueT end ) :
			  mStart( ( start < end ? start : end ) )
			, mEnd( ( start > end ? start : end ) )
		{}



		//
		//
		//
		bool operator==( const MyT& other ) const
		{
			return (
				   ( mStart == other.mStart )
				&& ( mEnd == other.mEnd )
			);
		}
		bool operator!=( const MyT& other ) const
		{
			return !( operator==( other ) );
		}



		//
		//
		//
		bool IsIn( const ValueT check_target ) const
		{
			return (
				   ( check_target >= mStart )
				&& ( check_target <= mEnd )
			);
		}
		bool IsOne() const
		{
			return mStart == mEnd;
		}



		//
		//
		//
		ValueT GetStart() const
		{
			return mStart;
		}
		ValueT GetEnd() const
		{
			return mEnd;
		}
		ValueT GetDistance() const
		{
			return mEnd - mStart;
		}



		//
		//
		//
		void Set( const ValueT new_value )
		{
			mStart = new_value;
			mEnd = new_value;
		}
		void Set( const ValueT new_start, const ValueT new_end )
		{
			mStart = new_start;
			mEnd = new_end;
		}
		void SetStart( const ValueT new_start )
		{
			mStart = new_start;
		}
		void SetEnd( const ValueT new_end )
		{
			mEnd = new_end;
		}



		//
		//
		//
		void AddAll( const ValueT add_value )
		{
			mStart += add_value;
			mEnd += add_value;
		}
		void AddStart( const ValueT add_value )
		{
			mStart += add_value;
		}
		void AddEnd( const ValueT add_value )
		{
			mEnd += add_value;
		}



	private:
		ValueT mStart;
		ValueT mEnd;
	};
}