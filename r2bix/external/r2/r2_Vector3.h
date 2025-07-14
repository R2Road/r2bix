//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.07.14 PM.04.34
// # Version			: 1.0.0
//

#pragma once

#include <cmath>

#include "r2_Epsilon.h"

namespace r2
{
	struct Vector3
	{
		Vector3() : x( 0.f ), y( 0.f ), z( 0.f )
		{}
		explicit Vector3( const float new_x, const float new_y, const float new_z ) : x( new_x ), y( new_y ), z( new_z )
		{}

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
	};



	inline bool operator==( const Vector3& v1, const Vector3& v2 )
	{
		return ( v1.x == v2.x ) && ( v1.y == v2.y ) && ( v1.z == v2.z );
	}
	inline bool operator!=( const Vector3& v1, const Vector3& v2 )
	{
		return !operator==( v1, v2 );
	}

	inline Vector3 operator+( const Vector3& v1, const Vector3& v2 )
	{
		return Vector3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}
	inline void operator+=( Vector3& v1, const Vector3& v2 )
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
	}

	inline Vector3 operator-( const Vector3& v1, const Vector3& v2 )
	{
		return Vector3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}
	inline void operator-=( Vector3& v1, const Vector3& v2 )
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
	}

	inline Vector3 operator*( const Vector3& v1, const float scalar )
	{
		return Vector3{ v1.x * scalar, v1.y * scalar, v1.z * scalar };
	}
	inline void operator*=( Vector3& v1, const float scalar )
	{
		v1.x *= scalar;
		v1.y *= scalar;
		v1.z *= scalar;
	}



	inline float length( const Vector3& v )
	{
		return std::sqrt( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) );
	}
	inline Vector3 normalize( const Vector3& v )
	{
		const float l = r2::length( v );
		return (
			  r2::epsilon_equal( l, 0.f )
			? Vector3{
				  0.f
				, 0.f
				, 0.f
			}
			: Vector3{
				  v.x / l
				, v.y / l
				, v.z / l
			}
		);
	}
	inline float dot( const Vector3& v1, const Vector3& v2 )
	{
		return ( v1.x * v2.x ) + ( v1.y * v2.y ) + ( v1.z * v2.z );
	}
	inline Vector3 cross( const Vector3& v1, const Vector3& v2 )
	{
		return Vector3{
			  ( v1.y * v2.z ) - ( v1.z * v2.y )
			, ( v1.z * v2.x ) - ( v1.x * v2.z )
			, ( v1.x * v2.y ) - ( v1.y * v2.x )
		};
	}
}