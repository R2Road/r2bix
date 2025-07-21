//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.07.14 PM.06.00
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_Degree.h"
#include "r2_Epsilon.h"
#include "r2_Math.h"
#include "r2_Radian.h"
#include "r2_Vector3.h"
#include "r2_Vector4.h"

namespace r2
{
	struct Quaternion
	{
		Quaternion() : w( 0.f ), x( 0.f ), y( 0.f ), z( 0.f )
		{}
		explicit Quaternion( const float new_w, const float new_x, const float new_y, const float new_z ) :
			  w( new_w )
			, x( new_x )
			, y( new_y )
			, z( new_z )
		{}

		explicit Quaternion( const Vector3 v ) :
			  w( 0 )
			, x( v.x )
			, y( v.y )
			, z( v.z )
		{}
		explicit Quaternion( const Vector3 axis, const Radian radian ) : w( 0.f ), x( 0.f ), y( 0.f ), z( 0.f )
		{
			w = std::cos( radian.Get() / 2.f );
			x = axis.x * std::sin( radian.Get() / 2.f );
			y = axis.y* std::sin( radian.Get() / 2.f );
			z = axis.z* std::sin( radian.Get() / 2.f );
		}
		explicit Quaternion( const Vector3 axis, const Degree degree ) : w( 0.f ), x( 0.f ), y( 0.f ), z( 0.f )
		{
			const Radian radian = r2::deg2rad( degree );

			w = std::cos( radian.Get() / 2.f );
			x = axis.x * std::sin( radian.Get() / 2.f );
			y = axis.y * std::sin( radian.Get() / 2.f );
			z = axis.z * std::sin( radian.Get() / 2.f );
		}

		explicit Quaternion( const Vector4 v ) :
			  w( 0 )
			, x( v.x )
			, y( v.y )
			, z( v.z )
		{}
		explicit Quaternion( const Vector4 axis, const Radian radian ) : w( 0.f ), x( 0.f ), y( 0.f ), z( 0.f )
		{
			w = std::cos( radian.Get() / 2.f );
			x = axis.x * std::sin( radian.Get() / 2.f );
			y = axis.y * std::sin( radian.Get() / 2.f );
			z = axis.z * std::sin( radian.Get() / 2.f );
		}
		explicit Quaternion( const Vector4 axis, const Degree degree ) : w( 0.f ), x( 0.f ), y( 0.f ), z( 0.f )
		{
			const Radian radian = r2::deg2rad( degree );

			w = std::cos( radian.Get() / 2.f );
			x = axis.x * std::sin( radian.Get() / 2.f );
			y = axis.y * std::sin( radian.Get() / 2.f );
			z = axis.z * std::sin( radian.Get() / 2.f );
		}

		float w;
		float x;
		float y;
		float z;
	};



	inline bool operator==( const Quaternion& a, const Quaternion& b )
	{
		return (
			   r2::epsilon_equal( a.w, b.w )
			&& r2::epsilon_equal( a.x, b.x )
			&& r2::epsilon_equal( a.y, b.y )
			&& r2::epsilon_equal( a.z, b.z )
		);
	}



	inline Quaternion operator*( const Quaternion& a, const Quaternion& b )
	{
		return Quaternion(
			  ( a.w * b.w ) - ( a.x * b.x ) - ( a.y * b.y ) - ( a.z * b.z )
			, ( a.w * b.x ) + ( a.x * b.w ) + ( a.y * b.z ) - ( a.z * b.y )
			, ( a.w * b.y ) + ( a.y * b.w ) + ( a.z * b.x ) - ( a.x * b.z )
			, ( a.w * b.z ) + ( a.z * b.w ) + ( a.x * b.y ) - ( a.y * b.x )
		);
	}



	inline Quaternion inverse( const Quaternion& q )
	{
		return Quaternion( q.w, -q.x, -q.y, -q.z );
	}



	inline Vector3 operator*( const Quaternion& q, const Vector3& v )
	{
		const Quaternion temp = ( q * Quaternion( v ) ) * inverse( q );
		return Vector3( temp.x, temp.y, temp.z );
	}
	inline Vector4 operator*( const Quaternion& q, const Vector4& v )
	{
		const Vector3 temp = q * Vector3( v.x, v.y, v.z );
		return Vector4( temp.x, temp.y, temp.z, 1 );
	}



	inline float length( const Quaternion& q )
	{
		return std::sqrt(
			  ( q.w * q.w )
			+ ( q.x * q.x )
			+ ( q.y * q.y )
			+ ( q.z * q.z )
		);
	}

	inline Quaternion normalize( const Quaternion& q )
	{
		const float l = length( q );

		return Quaternion(
			  q.w / l
			, q.x / l
			, q.y / l
			, q.z / l
		);
	}
}