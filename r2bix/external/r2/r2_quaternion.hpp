//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.05 PM.07.45
// # Version			: 1.1.0.0
//

#pragma once

#include "r2_degree.hpp"
#include "r2_epsilon.hpp"
#include "r2_math.hpp"
#include "r2_matrix33.hpp"
#include "r2_matrix44.hpp"
#include "r2_radian.hpp"
#include "r2_vector3.hpp"
#include "r2_vector4.hpp"

namespace r2
{
	struct Quaternion
	{
		constexpr Quaternion() : w( 0.f ), x( 0.f ), y( 0.f ), z( 0.f )
		{}
		explicit constexpr Quaternion( const float new_w, const float new_x, const float new_y, const float new_z ) :
			  w( new_w )
			, x( new_x )
			, y( new_y )
			, z( new_z )
		{}

		explicit constexpr Quaternion( const Vector3 v ) :
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

		explicit constexpr Quaternion( const Vector4 v ) :
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



	inline Matrix33 quat2mat33( const r2::Quaternion& q )
	{
		// REF : https://github.com/g-truc/glm/blob/master/glm/gtc/quaternion.inl
		// REF : mat3_cast

		const float xx( q.x * q.x );
		const float yy( q.y * q.y );
		const float zz( q.z * q.z );
		const float xz( q.x * q.z );
		const float xy( q.x * q.y );
		const float yz( q.y * q.z );
		const float wx( q.w * q.x );
		const float wy( q.w * q.y );
		const float wz( q.w * q.z );

		return r2::Matrix33(
			  ( 1 - ( 2 *  yy ) - ( 2 * zz ) )  , ( ( 2 * xy ) - ( 2 * wz ) )      , ( ( 2 * xz ) + ( 2 * wy ) )
			, ( ( 2 * xy ) + ( 2 * wz ) )       , ( 1 - ( 2 * xx ) - ( 2 * zz ) )  , ( ( 2 * yz ) - ( 2 * wx )  )
			, ( ( 2 * xz ) - ( 2 * wy ) )       , ( ( 2 * yz ) + ( 2 * wx )  )     , ( 1 - ( 2 * xx ) - ( 2 * yy ) )
		);
	}
	inline Matrix44 quat2mat44( const r2::Quaternion& q )
	{
		const Matrix33 temp = quat2mat33( q );

		return r2::Matrix44(
			  temp._11, temp._12, temp._13,        0
			, temp._21, temp._22, temp._23,        0
			, temp._31, temp._32, temp._33,        0
			,        0,        0,        0,        1
		);
	}



	inline r2::Quaternion mat2quat( const r2::Matrix33& m )
	{
		// REF : https://github.com/g-truc/glm/blob/master/glm/gtc/quaternion.inl
		// REF : quat_cast
		// glm 의 코드는 열 우선이다. 여기서는 행 우선이기 때문에 각 성분 참조가 전치 되어 있다.

		// 이 코드는 쿼터니언의 네 성분(x,y,z,w)의 제곱에 4를 곱하고 1을 뺀 값에 해당하는 값을 만든다.
		// quat2mat33 함수의 각 성분 계산 코드 참조
		float fourXSquaredMinus1 = m._11 - m._22 - m._33;
		float fourYSquaredMinus1 = m._22 - m._11 - m._33;
		float fourZSquaredMinus1 = m._33 - m._11 - m._22;
		// 행렬의 대각합 : 가장 일반적으로 사용, 나머지 세 값은 쿼터니언의 축 성분(x,y,z) 중 하나가 지배적일 때 사용
		float fourWSquaredMinus1 = m._11 + m._22 + m._33;

		int biggest_index = 0;
		float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if( fourXSquaredMinus1 > fourBiggestSquaredMinus1 )
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggest_index = 1;
		}
		if( fourYSquaredMinus1 > fourBiggestSquaredMinus1 )
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggest_index = 2;
		}
		if( fourZSquaredMinus1 > fourBiggestSquaredMinus1 )
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggest_index = 3;
		}

		float biggest_value = sqrt( fourBiggestSquaredMinus1 + 1.f ) * 0.5f;

		// 나머지 쿼터니언 성분들을 계산하는 데 사용되는 스케일링 팩터
		float mult = ( 0.25f / biggest_value );

		switch( biggest_index )
		{
		case 0:
			return r2::Quaternion( biggest_value, ( m._32 - m._23 ) * mult, ( m._13 - m._31 ) * mult, ( m._21 - m._12 ) * mult );
		case 1:
			return r2::Quaternion( ( m._32 - m._23 ) * mult, biggest_value, ( m._21 + m._12 ) * mult, ( m._13 + m._31 ) * mult );
		case 2:
			return r2::Quaternion( ( m._13 - m._31 ) * mult, ( m._21 + m._12 ) * mult, biggest_value, ( m._32 + m._23 ) * mult );
		case 3:
			return r2::Quaternion( ( m._21 - m._12 ) * mult, ( m._13 + m._31 ) * mult, ( m._32 + m._23 ) * mult, biggest_value );
		default:
			return r2::Quaternion( 1, 0, 0, 0 );
		}
	}
	inline r2::Quaternion mat2quat( const r2::Matrix44& m )
	{
		return mat2quat( r2::Matrix33(
			  m._11, m._12, m._13
			, m._21, m._22, m._23
			, m._31, m._32, m._33
		) );
	}
}