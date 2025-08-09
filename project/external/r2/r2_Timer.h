//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.05.19 AM.08.05
// # Version			: 1.0.1
//

#pragma once

#include <algorithm>
#include <limits>

#include "r2_Assert.h"
#include "r2_TypeTraits.h"

namespace r2
{
	template<typename T>
	class Timer
	{
	public:
		static_assert(
			   r2::is_same_v<T, float>
			|| r2::is_same_v<T, double>
			, "r2::Timer - Not Allowed Type"
		);

		using ValueT = T;

		static constexpr ValueT ValueMAX = std::numeric_limits<ValueT>::max();
		static constexpr ValueT ValueZERO = static_cast<ValueT>( 0 );
		static constexpr ValueT ValueONE = static_cast<ValueT>( 1 );



		Timer() :
			mAlive( false )
			, mLimitTime( ValueZERO )
			, mElapsedTime( ValueZERO )
		{}
		explicit Timer( const ValueT limit_time ) :
			mAlive( false )
			, mLimitTime( limit_time )
			, mElapsedTime( ValueZERO )
		{}
		explicit Timer( const ValueT limit_time, const bool on_timer ) :
			mAlive( on_timer )
			, mLimitTime( limit_time )
			, mElapsedTime( ValueZERO )
		{}



		//
		//
		//
		void Start()
		{
			mElapsedTime = ValueZERO;
			mAlive = true;
		}
		void Stop()
		{
			mAlive = false;
		}
		void Resume()
		{
			mAlive = true;
		}
		void Reset()
		{
			mElapsedTime = ValueZERO;
			mAlive = false;
		}



		//
		//
		//
		void Flip()
		{
			mElapsedTime = std::min( mElapsedTime, mLimitTime );
			mElapsedTime = mLimitTime - mElapsedTime;
		}



		//
		//
		//
		void SetLimitTime( const ValueT new_limit_time )
		{
			mLimitTime = new_limit_time;
		}
		void IncreaseLimitTime( const ValueT additional_time )
		{
			mLimitTime += additional_time;
		}



		//
		//
		//
		bool Update( const ValueT dt )
		{
			if( !mAlive )
			{
				return false;
			}

			R2ASSERT( dt <= ( ValueMAX - mElapsedTime ), "" );

			mElapsedTime += dt;

			if( mLimitTime <= mElapsedTime )
			{
				mAlive = false;
			}

			return mAlive;
		}



		//
		//
		//
		bool IsAlive() const
		{
			return mAlive;
		}
		bool IsDie() const
		{
			return !IsAlive();
		}
		ValueT GetElapsedTime() const
		{
			return mElapsedTime;
		}
		ValueT GetLimitTime() const
		{
			return mLimitTime;
		}
		//
		//
		//
		ValueT GetElapsedTimeRate() const
		{
			if( mElapsedTime >= mLimitTime )
			{
				return ValueONE;
			}
			else
			{
				return ( ValueZERO >= mLimitTime ? ValueZERO : mElapsedTime / mLimitTime );
			}
		}
		ValueT GetElapsedTimeInverseRate() const
		{
			return 1.f - GetElapsedTimeRate();
		}
		const ValueT GetElapsedTimePureRate() const
		{
			return ( ValueZERO >= mLimitTime ? ValueZERO : mElapsedTime / mLimitTime );
		}



	private:
		bool mAlive;
		ValueT mLimitTime;
		ValueT mElapsedTime;
	};
}
