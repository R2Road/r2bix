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

#include "r2_epsilon.hpp"

namespace r2
{
	class Radian
	{
	public:
		constexpr Radian() : mValue( 0.f )
		{}
		constexpr explicit Radian( const float new_value ) : mValue( new_value )
		{}

		bool operator==( const Radian radian ) const
		{
			return r2::epsilon_equal( mValue, radian.mValue );
		}
		bool operator!=( const Radian radian ) const
		{
			return !( *this == radian );
		}

		constexpr Radian operator+( const Radian radian ) const
		{
			return Radian( mValue + radian.mValue );
		}
		void operator+=( const Radian radian )
		{
			mValue += radian.mValue;
		}

		constexpr Radian operator-() const
		{
			return Radian( -mValue );
		}
		constexpr Radian operator-( const Radian radian ) const
		{
			return Radian( mValue - radian.mValue );
		}
		void operator-=( const Radian radian )
		{
			mValue -= radian.mValue;
		}

		constexpr Radian operator*( const float scalar ) const
		{
			return Radian( mValue * scalar );
		}
		void operator*=( const float scalar )
		{
			mValue *= scalar;
		}

		constexpr Radian operator/( const float scalar ) const
		{
			return Radian( mValue / scalar );
		}
		void operator/=( const float scalar )
		{
			mValue /= scalar;
		}

		constexpr float Get() const
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