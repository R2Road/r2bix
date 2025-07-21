//
// # Version Rule
// - 1.0.0.0 : ��� ����
// - 0.1.0.0 : ��� �߰�/����
// - 0.0.1.0 : ��� ����/����
// - 0.0.0.1 : ������ ��ȭ
//
// # Last Update		: 2025.07.21 PM.04.30
// # Version			: 1.1.0.0
//

#pragma once

#include "r2_Epsilon.h"

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
}