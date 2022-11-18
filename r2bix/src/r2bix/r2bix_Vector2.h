#pragma once

namespace r2bix
{
	struct Vector2
	{
		Vector2( float new_x, float new_y ) : x( new_x ), y( new_y ) {}

		float x = 0.f;
		float y = 0.f;
	};

	Vector2 operator+( const Vector2& v1, const Vector2& v2 )
	{
		return Vector2{ v1.x + v2.x, v1.y + v2.y };
	}
	void operator+=( Vector2& v1, const Vector2& v2 )
	{
		v1.x += v2.x;
		v1.y += v2.y;
	}

	Vector2 operator-( const Vector2& v1, const Vector2& v2 )
	{
		return Vector2{ v1.x - v2.x, v1.y - v2.y };
	}
	void operator-=( Vector2& v1, const Vector2& v2 )
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
	}

	Vector2 operator*( const Vector2& v1, const float scalar )
	{
		return Vector2{ v1.x * scalar, v1.y * scalar };
	}
	void operator*=( Vector2& v1, const float scalar )
	{
		v1.x *= scalar;
		v1.y *= scalar;
	}
}