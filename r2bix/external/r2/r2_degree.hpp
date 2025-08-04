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
	class Degree
	{
	public:
		constexpr Degree() : mValue( 0.f )
		{}
		constexpr explicit Degree( const float new_value ) : mValue( new_value )
		{}

		bool operator==( const Degree degree ) const
		{
			return r2::epsilon_equal( mValue, degree.mValue );
		}
		bool operator!=( const Degree degree ) const
		{
			return !( *this == degree );
		}

		constexpr Degree operator+( const Degree degree ) const
		{
			return Degree( mValue + degree.mValue );
		}
		void operator+=( const Degree degree )
		{
			mValue += degree.mValue;
		}

		constexpr Degree operator-() const
		{
			return Degree( -mValue );
		}
		constexpr Degree operator-( const Degree degree ) const
		{
			return Degree( mValue - degree.mValue );
		}
		void operator-=( const Degree degree )
		{
			mValue -= degree.mValue;
		}

		constexpr Degree operator*( const float scalar ) const
		{
			return Degree( mValue * scalar );
		}
		void operator*=( const float scalar )
		{
			mValue *= scalar;
		}

		constexpr Degree operator/( const float scalar ) const
		{
			return Degree( mValue / scalar );
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