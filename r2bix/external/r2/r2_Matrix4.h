//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.06.15 PM.03.30
// # Version			: 1.0.0.0
//

#pragma once

// REF : https://learn.microsoft.com/en-us/windows/win32/api/directxmath/ns-directxmath-xmmatrix?source=recommendations

#include "r2_Quaternion.h"

namespace r2
{
	struct Matrix4
	{
		Matrix4() :
			  _11( 1.f ), _12( 0.f ), _13( 0.f ), _14( 0.f )
			, _21( 0.f ), _22( 1.f ), _23( 0.f ), _24( 0.f )
			, _31( 0.f ), _32( 0.f ), _33( 1.f ), _34( 0.f )
			, _41( 0.f ), _42( 0.f ), _43( 0.f ), _44( 1.f )
		{}
		explicit Matrix4(
			  float __11, float __12, float __13, float __14
			, float __21, float __22, float __23, float __24
			, float __31, float __32, float __33, float __34
			, float __41, float __42, float __43, float __44
		) :
			  _11( __11 ), _12( __12 ), _13( __13 ), _14( __14 )
			, _21( __21 ), _22( __22 ), _23( __23 ), _24( __24 )
			, _31( __31 ), _32( __32 ), _33( __33 ), _34( __34 )
			, _41( __41 ), _42( __42 ), _43( __43 ), _44( __44 )
		{}

		explicit Matrix4( const r2::Quaternion q ) :
			  _11( 1 - ( 2 *  q.y * q.y ) - ( 2 * q.z * q.z ) )  , _12( ( 2 * q.x * q.y ) - ( 2 * q.z * q.w ) )      , _13( ( 2 * q.x * q.z ) + ( 2 * q.y * q.w ) )      , _14( 0 )
			, _21( ( 2 * q.x * q.y ) + ( 2 * q.z * q.w ) )       , _22( 1 - ( 2 * q.x * q.x ) - ( 2 * q.z * q.z ) )  , _23( ( 2 * q.y * q.z ) - ( 2 * q.x * q.w )  )     , _24( 0 )
			, _31( ( 2 * q.x * q.z ) - ( 2 * q.y * q.w ) )       , _32( ( 2 * q.y * q.z ) + ( 2 * q.x * q.w )  )     , _33( 1 - ( 2 * q.x * q.x ) - ( 2 * q.y * q.y ) )  , _34( 0 )
			, _41( 0 )                                           , _42( 0 )                                          , _43( 0 )                                          , _44( 1 )
		{}

		float _11;
		float _12;
		float _13;
		float _14;

		float _21;
		float _22;
		float _23;
		float _24;

		float _31;
		float _32;
		float _33;
		float _34;

		float _41;
		float _42;
		float _43;
		float _44;
	};



	inline bool operator==( const Matrix4& m1, const Matrix4& m2 )
	{
		return (
			   ( m1._11 == m2._11 ) && ( m1._12 == m2._12 ) && ( m1._13 == m2._13 ) && ( m1._14 == m2._14 )
			&& ( m1._21 == m2._21 ) && ( m1._22 == m2._22 ) && ( m1._23 == m2._23 ) && ( m1._24 == m2._24 )
			&& ( m1._31 == m2._31 ) && ( m1._32 == m2._32 ) && ( m1._33 == m2._33 ) && ( m1._34 == m2._34 )
			&& ( m1._41 == m2._41 ) && ( m1._42 == m2._42 ) && ( m1._43 == m2._43 ) && ( m1._44 == m2._44 )
		);
	}
	inline bool operator!=( const Matrix4& m1, const Matrix4& m2 )
	{
		return !operator==( m1, m2 );
	}



	inline Matrix4 operator+( const Matrix4& m, const float s )
	{
		return Matrix4{
			  ( m._11 + s ) , ( m._12 + s ) , ( m._13 + s ) , ( m._14 + s )
			, ( m._21 + s ) , ( m._22 + s ) , ( m._23 + s ) , ( m._24 + s )
			, ( m._31 + s ) , ( m._32 + s ) , ( m._33 + s ) , ( m._34 + s )
			, ( m._41 + s ) , ( m._42 + s ) , ( m._43 + s ) , ( m._44 + s )
		};
	}
	inline void operator+=( Matrix4& m, const float s )
	{
		m._11 += s; m._12 += s; m._13 += s; m._14 += s;
		m._21 += s; m._22 += s; m._23 += s; m._24 += s;
		m._31 += s; m._32 += s; m._33 += s; m._34 += s;
		m._41 += s; m._42 += s; m._43 += s; m._44 += s;
	}
	inline Matrix4 operator-( const Matrix4& m, const float s )
	{
		return Matrix4{
			  ( m._11 - s ) , ( m._12 - s ) , ( m._13 - s ) , ( m._14 - s )
			, ( m._21 - s ) , ( m._22 - s ) , ( m._23 - s ) , ( m._24 - s )
			, ( m._31 - s ) , ( m._32 - s ) , ( m._33 - s ) , ( m._34 - s )
			, ( m._41 - s ) , ( m._42 - s ) , ( m._43 - s ) , ( m._44 - s )
		};
	}
	inline void operator-=( Matrix4& m, const float s )
	{
		m._11 -= s; m._12 -= s; m._13 -= s; m._14 -= s;
		m._21 -= s; m._22 -= s; m._23 -= s; m._24 -= s;
		m._31 -= s; m._32 -= s; m._33 -= s; m._34 -= s;
		m._41 -= s; m._42 -= s; m._43 -= s; m._44 -= s;
	}



	inline Matrix4 operator+( const Matrix4& m1, const Matrix4& m2 )
	{
		return Matrix4{
			  ( m1._11 + m2._11 ) , ( m1._12 + m2._12 ) , ( m1._13 + m2._13 ) , ( m1._14 + m2._14 )
			, ( m1._21 + m2._21 ) , ( m1._22 + m2._22 ) , ( m1._23 + m2._23 ) , ( m1._24 + m2._24 )
			, ( m1._31 + m2._31 ) , ( m1._32 + m2._32 ) , ( m1._33 + m2._33 ) , ( m1._34 + m2._34 )
			, ( m1._41 + m2._41 ) , ( m1._42 + m2._42 ) , ( m1._43 + m2._43 ) , ( m1._44 + m2._44 )
		};
	}
	inline void operator+=( Matrix4& m1, const Matrix4& m2 )
	{
		m1._11 += m2._11; m1._12 += m2._12; m1._13 += m2._13; m1._14 += m2._14;
		m1._21 += m2._21; m1._22 += m2._22; m1._23 += m2._23; m1._24 += m2._24;
		m1._31 += m2._31; m1._32 += m2._32; m1._33 += m2._33; m1._34 += m2._34;
		m1._41 += m2._41; m1._42 += m2._42; m1._43 += m2._43; m1._44 += m2._44;
	}
	inline Matrix4 operator-( const Matrix4& m1, const Matrix4& m2 )
	{
		return Matrix4{
			  ( m1._11 - m2._11 ), ( m1._12 - m2._12 ), ( m1._13 - m2._13 ), ( m1._14 - m2._14 )
			, ( m1._21 - m2._21 ), ( m1._22 - m2._22 ), ( m1._23 - m2._23 ), ( m1._24 - m2._24 )
			, ( m1._31 - m2._31 ), ( m1._32 - m2._32 ), ( m1._33 - m2._33 ), ( m1._34 - m2._34 )
			, ( m1._41 - m2._41 ), ( m1._42 - m2._42 ), ( m1._43 - m2._43 ), ( m1._44 - m2._44 )
		};
	}
	inline void operator-=( Matrix4& m1, const Matrix4& m2 )
	{
		m1._11 -= m2._11; m1._12 -= m2._12; m1._13 -= m2._13; m1._14 -= m2._14;
		m1._21 -= m2._21; m1._22 -= m2._22; m1._23 -= m2._23; m1._24 -= m2._24;
		m1._31 -= m2._31; m1._32 -= m2._32; m1._33 -= m2._33; m1._34 -= m2._34;
		m1._41 -= m2._41; m1._42 -= m2._42; m1._43 -= m2._43; m1._44 -= m2._44;
	}



	inline Matrix4 operator*( const Matrix4& m1, const Matrix4& m2 )
	{
		//
		// 가로 x 세로
		//
		// 11, 12, 13, 14
		// 21, 22, 23, 24
		// 31, 32, 33, 34
		// 41, 42, 43, 44
		return Matrix4{
			  ( m1._11 * m2._11 ) + ( m1._12 * m2._21 ) + ( m1._13 * m2._31 ) + ( m1._14 * m2._41 )
			, ( m1._11 * m2._12 ) + ( m1._12 * m2._22 ) + ( m1._13 * m2._32 ) + ( m1._14 * m2._42 )
			, ( m1._11 * m2._13 ) + ( m1._12 * m2._23 ) + ( m1._13 * m2._33 ) + ( m1._14 * m2._43 )
			, ( m1._11 * m2._14 ) + ( m1._12 * m2._24 ) + ( m1._13 * m2._34 ) + ( m1._14 * m2._44 )

			, ( m1._21 * m2._11 ) + ( m1._22 * m2._21 ) + ( m1._23 * m2._31 ) + ( m1._24 * m2._41 )
			, ( m1._21 * m2._12 ) + ( m1._22 * m2._22 ) + ( m1._23 * m2._32 ) + ( m1._24 * m2._42 )
			, ( m1._21 * m2._13 ) + ( m1._22 * m2._23 ) + ( m1._23 * m2._33 ) + ( m1._24 * m2._43 )
			, ( m1._21 * m2._14 ) + ( m1._22 * m2._24 ) + ( m1._23 * m2._34 ) + ( m1._24 * m2._44 )

			, ( m1._31 * m2._11 ) + ( m1._32 * m2._21 ) + ( m1._33 * m2._31 ) + ( m1._34 * m2._41 )
			, ( m1._31 * m2._12 ) + ( m1._32 * m2._22 ) + ( m1._33 * m2._32 ) + ( m1._34 * m2._42 )
			, ( m1._31 * m2._13 ) + ( m1._32 * m2._23 ) + ( m1._33 * m2._33 ) + ( m1._34 * m2._43 )
			, ( m1._31 * m2._14 ) + ( m1._32 * m2._24 ) + ( m1._33 * m2._34 ) + ( m1._34 * m2._44 )

			, ( m1._41 * m2._11 ) + ( m1._42 * m2._21 ) + ( m1._43 * m2._31 ) + ( m1._44 * m2._41 )
			, ( m1._41 * m2._12 ) + ( m1._42 * m2._22 ) + ( m1._43 * m2._32 ) + ( m1._44 * m2._42 )
			, ( m1._41 * m2._13 ) + ( m1._42 * m2._23 ) + ( m1._43 * m2._33 ) + ( m1._44 * m2._43 )
			, ( m1._41 * m2._14 ) + ( m1._42 * m2._24 ) + ( m1._43 * m2._34 ) + ( m1._44 * m2._44 )
		};
	}
	inline void operator*=( Matrix4& m1, const Matrix4& m2 )
	{
		m1 = ( m1 * m2 );
	}
}


#include "r2_Math.h"
#include "r2_Vector4.h"

//
// DX : V x M
// Opengl : M x V
// 무엇을 앞에 두고 곱하냐의 차이가 있기 때문에 이동 행렬등을 만들 때 위치의 차이가 생긴다.
// DX의 경우 41, 42, 43 값을 쓰면 되는데
// OpenGL은 14, 24, 34 값을 쓴다.
//

namespace r2
{
	inline Vector4 operator*( const Matrix4& m, const Vector4& v )
	{
		//
		// 가로 x 세로
		//
		// 11, 12, 13, 14
		// 21, 22, 23, 24
		// 31, 32, 33, 34
		// 41, 42, 43, 44
		return Vector4{
			  ( m._11 * v.x ) + ( m._12 * v.y ) + ( m._13 * v.z ) + ( m._14 * v.w )
			, ( m._21 * v.x ) + ( m._22 * v.y ) + ( m._23 * v.z ) + ( m._24 * v.w )
			, ( m._31 * v.x ) + ( m._32 * v.y ) + ( m._33 * v.z ) + ( m._34 * v.w )
			, ( m._41 * v.x ) + ( m._42 * v.y ) + ( m._43 * v.z ) + ( m._44 * v.w )
		};
	}



	inline Matrix4 BuildMatrix4_Translate( const float x, const float y, const float z )
	{
		//
		//  -,  -,  -,  x
		//  -,  -,  -,  y
		//  -,  -,  -,  z
		//  -,  -,  -,  -
		//

		Matrix4 ret;

		ret._14 = x;
		ret._24 = y;
		ret._34 = z;

		return ret;
	}

	inline Matrix4 BuildMatrix4_Scale( const float x, const float y, const float z )
	{
		//
		//  x,  -,  -,  -
		//  -,  y,  -,  -
		//  -,  -,  z,  -
		//  -,  -,  -,  -
		//

		Matrix4 ret;

		ret._11 = x;
		ret._22 = y;
		ret._33 = z;

		return ret;
	}


	//
	// 오른손 좌표계
	// > 축 기준 반시계 방향 회전이 기본
	//
	inline Matrix4 BuildMatrix4_RotationX( const r2::Degree degree )
	{
		//
		//  -,  -,  -,  -
		//  -,  c, -s,  -
		//  -,  s,  c,  -
		//  -,  -,  -,  -
		//

		const Radian radian = r2::deg2rad( degree );

		Matrix4 ret;

		// diagonal
		ret._22 = std::cos( radian.Get() );
		ret._33 = std::cos( radian.Get() );

		ret._23 = -std::sin( radian.Get() );
		ret._32 = std::sin( radian.Get() );

		return ret;
	}
	inline Matrix4 BuildMatrix4_RotationY( const r2::Degree degree )
	{
		//
		//  c,  -,  s,  -
		//  -,  -,  -,  -
		// -s,  -,  c,  -
		//  -,  -,  -,  -
		//

		const Radian radian = r2::deg2rad( degree );

		Matrix4 ret;

		// diagonal
		ret._11 = std::cos( radian.Get() );
		ret._33 = std::cos( radian.Get() );

		ret._13 = std::sin( radian.Get() );
		ret._31 = -std::sin( radian.Get() );

		return ret;
	}
	inline Matrix4 BuildMatrix4_RotationZ( const r2::Degree degree )
	{
		//
		//  c, -s,  -,  -
		//  s,  c,  -,  -
		//  -,  -,  -,  -
		//  -,  -,  -,  -
		//

		const Radian radian = r2::deg2rad( degree );

		Matrix4 ret;

		// diagonal
		ret._11 = std::cos( radian.Get() );
		ret._22 = std::cos( radian.Get() );

		ret._12 = -std::sin( radian.Get() );
		ret._21 = std::sin( radian.Get() );

		return ret;
	}
}