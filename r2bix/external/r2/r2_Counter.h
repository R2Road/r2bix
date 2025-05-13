#pragma once

#include <algorithm>
#include <numeric>

#include "r2_Assert.h"
#include "r2_TypeTraits.h"

namespace r2
{
	template<typename T>
	class Counter
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
			, "r2::Counter - Not Allowed Type"
		);



		using ValueT = T;
		static const ValueT ValueMAX = std::numeric_limits<ValueT>::max();



		Counter() : mCount( 0 )
		{}
		explicit Counter( const ValueT count ) : mCount( count )
		{}



		//
		// Getter
		//
		bool IsAlive( const ValueT limit_number ) const
		{
			return ( limit_number > mCount );
		}
		bool IsDie( const ValueT limit_number ) const
		{
			return !IsAlive( limit_number );
		}
		ValueT GetCount() const
		{
			return mCount;
		}



		//
		//
		//
		inline void Reset( const ValueT new_count )
		{
			mCount = new_count;
		}
		inline void Reset()
		{
			Reset( 0 );
		}



		//
		//
		//
		inline void Increase( const ValueT increase_amount )
		{
			R2ASSERT( increase_amount <= ( ValueMAX - mCount ), "" );

			mCount = (
				  increase_amount <= ( ValueMAX - mCount )
				? mCount + increase_amount
				: ValueMAX
			);
		}
		inline void Increase()
		{
			Increase( 1 );
		}



	private:
		ValueT mCount;
	};
}
