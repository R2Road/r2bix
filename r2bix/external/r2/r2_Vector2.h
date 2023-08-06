//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.06.17 PM.02.12
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	struct Vector2
	{
		Vector2() : x( 0.f ), y( 0.f )
		{}
		explicit Vector2( const float new_x, const float new_y ) : x( new_x ), y( new_y )
		{}

		float x = 0.f;
		float y = 0.f;
	};

	inline bool operator==( const Vector2& v1, const Vector2& v2 )
	{
		return ( v1.x == v2.x ) && ( v1.y == v2.y );
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