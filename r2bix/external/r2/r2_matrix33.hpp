//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.07.28 PM.05.00
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_epsilon.hpp"

namespace r2
{
	struct Matrix33
	{
		constexpr Matrix33() :
			  _11( 1.f ), _12( 0.f ), _13( 0.f )
			, _21( 0.f ), _22( 1.f ), _23( 0.f )
			, _31( 0.f ), _32( 0.f ), _33( 1.f )
		{}
		explicit constexpr Matrix33(
			  float __11, float __12, float __13
			, float __21, float __22, float __23
			, float __31, float __32, float __33
		) :
			  _11( __11 ), _12( __12 ), _13( __13 )
			, _21( __21 ), _22( __22 ), _23( __23 )
			, _31( __31 ), _32( __32 ), _33( __33 )
		{}

		float _11;
		float _12;
		float _13;

		float _21;
		float _22;
		float _23;

		float _31;
		float _32;
		float _33;
	};



	inline bool operator==( const Matrix33& m1, const Matrix33& m2 )
	{
		return (
			   ( m1._11 == m2._11 ) && ( m1._12 == m2._12 ) && ( m1._13 == m2._13 )
			&& ( m1._21 == m2._21 ) && ( m1._22 == m2._22 ) && ( m1._23 == m2._23 )
			&& ( m1._31 == m2._31 ) && ( m1._32 == m2._32 ) && ( m1._33 == m2._33 )
		);
	}
	inline bool operator!=( const Matrix33& m1, const Matrix33& m2 )
	{
		return !operator==( m1, m2 );
	}



	inline Matrix33 operator+( const Matrix33& m, const float s )
	{
		return Matrix33{
			  ( m._11 + s ) , ( m._12 + s ) , ( m._13 + s )
			, ( m._21 + s ) , ( m._22 + s ) , ( m._23 + s )
			, ( m._31 + s ) , ( m._32 + s ) , ( m._33 + s )
		};
	}
	inline void operator+=( Matrix33& m, const float s )
	{
		m._11 += s; m._12 += s; m._13 += s;
		m._21 += s; m._22 += s; m._23 += s;
		m._31 += s; m._32 += s; m._33 += s;
	}
	inline Matrix33 operator-( const Matrix33& m, const float s )
	{
		return Matrix33{
			  ( m._11 - s ) , ( m._12 - s ) , ( m._13 - s )
			, ( m._21 - s ) , ( m._22 - s ) , ( m._23 - s )
			, ( m._31 - s ) , ( m._32 - s ) , ( m._33 - s )
		};
	}
	inline void operator-=( Matrix33& m, const float s )
	{
		m._11 -= s; m._12 -= s; m._13 -= s;
		m._21 -= s; m._22 -= s; m._23 -= s;
		m._31 -= s; m._32 -= s; m._33 -= s;
	}
	inline Matrix33 operator*( const Matrix33& m, const float s )
	{
		return Matrix33{
			  ( m._11 * s ) , ( m._12 * s ) , ( m._13 * s )
			, ( m._21 * s ) , ( m._22 * s ) , ( m._23 * s )
			, ( m._31 * s ) , ( m._32 * s ) , ( m._33 * s )
		};
	}
	inline void operator*=( Matrix33& m, const float s )
	{
		m._11 *= s; m._12 *= s; m._13 *= s;
		m._21 *= s; m._22 *= s; m._23 *= s;
		m._31 *= s; m._32 *= s; m._33 *= s;
	}



	inline Matrix33 operator+( const Matrix33& m1, const Matrix33& m2 )
	{
		return Matrix33{
			  ( m1._11 + m2._11 ) , ( m1._12 + m2._12 ) , ( m1._13 + m2._13 )
			, ( m1._21 + m2._21 ) , ( m1._22 + m2._22 ) , ( m1._23 + m2._23 )
			, ( m1._31 + m2._31 ) , ( m1._32 + m2._32 ) , ( m1._33 + m2._33 )
		};
	}
	inline void operator+=( Matrix33& m1, const Matrix33& m2 )
	{
		m1._11 += m2._11; m1._12 += m2._12; m1._13 += m2._13;
		m1._21 += m2._21; m1._22 += m2._22; m1._23 += m2._23;
		m1._31 += m2._31; m1._32 += m2._32; m1._33 += m2._33;
	}
	inline Matrix33 operator-( const Matrix33& m1, const Matrix33& m2 )
	{
		return Matrix33{
			  ( m1._11 - m2._11 ), ( m1._12 - m2._12 ), ( m1._13 - m2._13 )
			, ( m1._21 - m2._21 ), ( m1._22 - m2._22 ), ( m1._23 - m2._23 )
			, ( m1._31 - m2._31 ), ( m1._32 - m2._32 ), ( m1._33 - m2._33 )
		};
	}
	inline void operator-=( Matrix33& m1, const Matrix33& m2 )
	{
		m1._11 -= m2._11; m1._12 -= m2._12; m1._13 -= m2._13;
		m1._21 -= m2._21; m1._22 -= m2._22; m1._23 -= m2._23;
		m1._31 -= m2._31; m1._32 -= m2._32; m1._33 -= m2._33;
	}



	inline Matrix33 operator*( const Matrix33& m1, const Matrix33& m2 )
	{
		//
		// 가로 x 세로
		//
		// 11, 12, 13
		// 21, 22, 23
		// 31, 32, 33
		return Matrix33{
			  ( m1._11 * m2._11 ) + ( m1._12 * m2._21 ) + ( m1._13 * m2._31 )
			, ( m1._11 * m2._12 ) + ( m1._12 * m2._22 ) + ( m1._13 * m2._32 )
			, ( m1._11 * m2._13 ) + ( m1._12 * m2._23 ) + ( m1._13 * m2._33 )

			, ( m1._21 * m2._11 ) + ( m1._22 * m2._21 ) + ( m1._23 * m2._31 )
			, ( m1._21 * m2._12 ) + ( m1._22 * m2._22 ) + ( m1._23 * m2._32 )
			, ( m1._21 * m2._13 ) + ( m1._22 * m2._23 ) + ( m1._23 * m2._33 )

			, ( m1._31 * m2._11 ) + ( m1._32 * m2._21 ) + ( m1._33 * m2._31 )
			, ( m1._31 * m2._12 ) + ( m1._32 * m2._22 ) + ( m1._33 * m2._32 )
			, ( m1._31 * m2._13 ) + ( m1._32 * m2._23 ) + ( m1._33 * m2._33 )
		};
	}
	inline void operator*=( Matrix33& m1, const Matrix33& m2 )
	{
		m1 = ( m1 * m2 );
	}



	inline Matrix33 inverse( const Matrix33 m )
	{
        //
		// # 일반적인 3 x 3 행렬의 역행렬 공식
		//   1. 행렬식(determinant)을 계산
		//   2. 각 원소의 여인수(cofactor)를 이용하여 수반 행렬(adjugate matrix) 생성
		//   3. 수반 행렬을 행렬식으로 나누는 방식
		// 
		//   A = 11 12 13    |   iA = 1/det(A) * ( ( 22 * 33 ) - ( 23 * 32 ) ), ( ( 13 * 32 ) - ( 12 * 33 ) ), ( ( 12 * 23 ) - ( 13 * 22 ) )
		//       21 22 23    |                   ( ( 23 * 31 ) - ( 21 * 33 ) ), ( ( 11 * 33 ) - ( 13 * 31 ) ), ( ( 13 * 21 ) - ( 11 * 23 ) )
		//       31 32 33    |	                 ( ( 21 * 32 ) - ( 22 * 31 ) ), ( ( 12 * 31 ) - ( 11 * 32 ) ), ( ( 11 * 22 ) - ( 12 * 21 ) )
		// 
		// # Determinant
		//   det(A) =   ( 11( ( 22 * 33 ) - ( 23 * 32 ) ) )
		//            - ( 12( ( 21 * 33 ) - ( 23 * 31 ) ) )
		//            + ( 13( ( 21 * 32 ) - ( 22 * 31 ) ) )
		//   det(A) == 0 이면 역행렬을 가질 수 없다.
		//

		const float inv_det = (
			1 / (
				  ( m._11 * ( ( m._22 * m._33 ) - ( m._23 * m._32 ) ) )
				- ( m._12 * ( ( m._21 * m._33 ) - ( m._23 * m._31 ) ) )
				+ ( m._13 * ( ( m._21 * m._32 ) - ( m._22 * m._31 ) ) )
			)
		);
		return (
			  r2::epsilon_equal( 0.f, inv_det )
			? Matrix33()
			: Matrix33(
				  ( ( m._22 * m._33 ) - ( m._23 * m._32 ) ) * inv_det, ( ( m._13 * m._32 ) - ( m._12 * m._33 ) ) * inv_det, ( ( m._12 * m._23 ) - ( m._13 * m._22 ) ) * inv_det
				, ( ( m._23 * m._31 ) - ( m._21 * m._33 ) ) * inv_det, ( ( m._11 * m._33 ) - ( m._13 * m._31 ) ) * inv_det, ( ( m._13 * m._21 ) - ( m._11 * m._23 ) ) * inv_det
				, ( ( m._21 * m._32 ) - ( m._22 * m._31 ) ) * inv_det, ( ( m._12 * m._31 ) - ( m._11 * m._32 ) ) * inv_det, ( ( m._11 * m._22 ) - ( m._12 * m._21 ) ) * inv_det
			)
		);
	}
}