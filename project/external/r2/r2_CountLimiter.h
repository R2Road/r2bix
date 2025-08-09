#pragma once

#include <algorithm>
#include <numeric>

#include "r2_Assert.h"
#include "r2_TypeTraits.h"

namespace r2
{
	template<typename T>
	class CountLimiter
	{
	public:
		static_assert(
			   r2::is_same_v<T, char>
			|| r2::is_same_v<T, unsigned char>
			|| r2::is_same_v<T, short>
			|| r2::is_same_v<T, unsigned short>
			|| r2::is_same_v<T, int>
			|| r2::is_same_v<T, unsigned int>
			|| r2::is_same_v<T, long long int>
			|| r2::is_same_v<T, unsigned long long int>
			, "r2::CountLimiter - Not Allowed Type"
		);



		using ValueT = T;
		static const ValueT ValueMAX = std::numeric_limits<ValueT>::max();



		CountLimiter() : mAlive( false ), mLimit( 0 ), mCount( 0 )
		{}
		explicit CountLimiter( const ValueT limit ) : mAlive( true ), mLimit( limit ), mCount( 0 )
		{}



		//
		//
		//
		bool IsAlive() const
		{
			return mAlive;
		}
		bool IsDie() const
		{
			return !mAlive;
		}
		ValueT GetCount() const
		{
			return mCount;
		}
		ValueT GetLimit() const
		{
			return mLimit;
		}



		//
		//
		//
		inline void ReStart()
		{
			mCount = 0;
			mAlive = ( mLimit > mCount );
		}
		inline void Reset( const ValueT limit )
		{
			mLimit = limit;
			ReStart();
		}



		//
		//
		//
		inline bool Increase( const ValueT increase_amount )
		{
			if( !mAlive )
			{
				return false;
			}

			increaseProcess( increase_amount );

			return mAlive;
		}
		inline bool Increase()
		{
			return Increase( 1 );
		}
	private:
		inline void increaseProcess( ValueT increase_amount )
		{
			R2ASSERT( increase_amount <= ( ValueMAX - mCount ), "" );

			mCount = std::min( ValueMAX, mCount + increase_amount );
			mAlive = ( mLimit > mCount );
		}



	private:
		bool mAlive;
		ValueT mLimit;
		ValueT mCount;
	};
}
