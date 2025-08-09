//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.04 PM.04.30
// # Version			: 1.2.1.0
//

#pragma once

#include <cmath>

#include "r2_epsilon.hpp"

namespace r2
{
	struct Vector2
	{
		constexpr Vector2() : x( 0.f ), y( 0.f )
		{}
		explicit constexpr Vector2( const float new_x, const float new_y ) : x( new_x ), y( new_y )
		{}

		float x = 0.f;
		float y = 0.f;
	};

	inline bool operator==( const Vector2& v1, const Vector2& v2 )
	{
		return (
			   r2::epsilon_equal( v1.x, v2.x )
			&& r2::epsilon_equal( v1.y, v2.y )
		);
	}
	inline bool operator!=( const Vector2& v1, const Vector2& v2 )
	{
		return !operator==( v1, v2 );
	}

	inline Vector2 operator+( const Vector2& v1, const Vector2& v2 )
	{
		return Vector2{ v1.x + v2.x, v1.y + v2.y };
	}
	inline void operator+=( Vector2& v1, const Vector2& v2 )
	{
		v1.x += v2.x;
		v1.y += v2.y;
	}

	inline Vector2 operator-( const Vector2& v1 )
	{
		return Vector2{ -v1.x, -v1.y };
	}
	inline Vector2 operator-( const Vector2& v1, const Vector2& v2 )
	{
		return Vector2{ v1.x - v2.x, v1.y - v2.y };
	}
	inline void operator-=( Vector2& v1, const Vector2& v2 )
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
	}

	inline Vector2 operator*( const Vector2& v1, const float scalar )
	{
		return Vector2{ v1.x * scalar, v1.y * scalar };
	}
	inline void operator*=( Vector2& v1, const float scalar )
	{
		v1.x *= scalar;
		v1.y *= scalar;
	}



	inline float length( const Vector2& v )
	{
		return std::sqrt( ( v.x * v.x ) + ( v.y * v.y ) );
	}
	inline Vector2 normalize( const Vector2& v )
	{
		const float l = r2::length( v );
		return (
			  r2::epsilon_equal( l, 0.f )
			? Vector2{
				  0.f
				, 0.f
			}
			: Vector2{
				  v.x / l
				, v.y / l
			}
		);
	}
	inline float dot( const Vector2& v1, const Vector2& v2 )
	{
		return ( v1.x * v2.x ) + ( v1.y * v2.y );
	}
	inline float cross( const Vector2& v1, const Vector2& v2 )
	{
		return ( v1.x * v2.y ) - ( v1.y * v2.x );
	}
}