//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.07.18 PM.05.00
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_Epsilon.h"

namespace r2
{
	class Radian
	{
	public:
		Radian() : mValue( 0.f )
		{}
		explicit Radian( const float new_value ) : mValue( new_value )
		{}

		bool operator==( const Radian radian ) const
		{
			return r2::epsilon_equal( mValue, radian.mValue );
		}
		bool operator!=( const Radian radian ) const
		{
			return !( *this == radian );
		}

		Radian operator+( const Radian radian ) const
		{
			return Radian( mValue + radian.mValue );
		}
		void operator+=( const Radian radian )
		{
			mValue += radian.mValue;
		}

		Radian operator-() const
		{
			return Radian( -mValue );
		}
		Radian operator-( const Radian radian ) const
		{
			return Radian( mValue - radian.mValue );
		}
		void operator-=( const Radian radian )
		{
			mValue -= radian.mValue;
		}

		Radian operator*( const float scalar ) const
		{
			return Radian( mValue * scalar );
		}
		void operator*=( const float scalar )
		{
			mValue *= scalar;
		}

		float Get() const
		{
			return mValue;
		}
		void Set( const float new_value )
		{
			mValue = new_value;
		}

	private:
		float mValue;
	};
}