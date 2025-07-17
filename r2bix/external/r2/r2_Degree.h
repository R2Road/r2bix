//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.07.17 PM.11.40
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_Epsilon.h"

namespace r2
{
	class Degree
	{
	public:
		Degree() : mValue( 0.f )
		{}
		explicit Degree( const float new_value ) : mValue( new_value )
		{}

		bool operator==( const Degree degree )
		{
			return r2::epsilon_equal( mValue, degree.mValue );
		}
		bool operator!=( const Degree degree )
		{
			return !( *this == degree );
		}

		Degree operator+( const Degree degree )
		{
			return Degree( mValue + degree.mValue );
		}
		void operator+=( const Degree degree )
		{
			mValue += degree.mValue;
		}

		Degree operator-( const Degree degree )
		{
			return Degree( mValue - degree.mValue );
		}
		void operator-=( const Degree degree )
		{
			mValue -= degree.mValue;
		}

		Degree operator*( const float scalar ) const
		{
			return Degree( mValue * scalar );
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