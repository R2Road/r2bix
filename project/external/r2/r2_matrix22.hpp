//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.07.27 PM.04.00
// # Version			: 1.0.0.0
//

#pragma once

// REF : https://learn.microsoft.com/en-us/windows/win32/api/directxmath/ns-directxmath-xmmatrix?source=recommendations

#include "r2_epsilon.hpp"

namespace r2
{
	struct Matrix22
	{
		constexpr Matrix22() :
			  _11( 1.f ), _12( 0.f )
			, _21( 0.f ), _22( 1.f )
		{}
		explicit constexpr Matrix22(
			  float __11, float __12
			, float __21, float __22
		) :
			  _11( __11 ), _12( __12 )
			, _21( __21 ), _22( __22 )
		{}

		float _11;
		float _12;

		float _21;
		float _22;
	};



	inline bool operator==( const Matrix22& m1, const Matrix22& m2 )
	{
		return (
			   ( m1._11 == m2._11 ) && ( m1._12 == m2._12 )
			&& ( m1._21 == m2._21 ) && ( m1._22 == m2._22 )
		);
	}
	inline bool operator!=( const Matrix22& m1, const Matrix22& m2 )
	{
		return !operator==( m1, m2 );
	}



	inline Matrix22 operator+( const Matrix22& m, const float s )
	{
		return Matrix22{
			  ( m._11 + s ) , ( m._12 + s )
			, ( m._21 + s ) , ( m._22 + s )
		};
	}
	inline void operator+=( Matrix22& m, const float s )
	{
		m._11 += s; m._12 += s;
		m._21 += s; m._22 += s;
	}
	inline Matrix22 operator-( const Matrix22& m, const float s )
	{
		return Matrix22{
			  ( m._11 - s ) , ( m._12 - s )
			, ( m._21 - s ) , ( m._22 - s )
		};
	}
	inline void operator-=( Matrix22& m, const float s )
	{
		m._11 -= s; m._12 -= s;
		m._21 -= s; m._22 -= s;
	}
	inline Matrix22 operator*( const Matrix22& m, const float s )
	{
		return Matrix22{
			  ( m._11 * s ) , ( m._12 * s )
			, ( m._21 * s ) , ( m._22 * s )
		};
	}
	inline void operator*=( Matrix22& m, const float s )
	{
		m._11 *= s; m._12 *= s;
		m._21 *= s; m._22 *= s;
	}



	inline Matrix22 operator+( const Matrix22& m1, const Matrix22& m2 )
	{
		return Matrix22{
			  ( m1._11 + m2._11 ) , ( m1._12 + m2._12 )
			, ( m1._21 + m2._21 ) , ( m1._22 + m2._22 )
		};
	}
	inline void operator+=( Matrix22& m1, const Matrix22& m2 )
	{
		m1._11 += m2._11; m1._12 += m2._12;
		m1._21 += m2._21; m1._22 += m2._22;
	}
	inline Matrix22 operator-( const Matrix22& m1, const Matrix22& m2 )
	{
		return Matrix22{
			  ( m1._11 - m2._11 ), ( m1._12 - m2._12 )
			, ( m1._21 - m2._21 ), ( m1._22 - m2._22 )
		};
	}
	inline void operator-=( Matrix22& m1, const Matrix22& m2 )
	{
		m1._11 -= m2._11; m1._12 -= m2._12;
		m1._21 -= m2._21; m1._22 -= m2._22;
	}



	inline Matrix22 operator*( const Matrix22& m1, const Matrix22& m2 )
	{
		//
		// 가로 x 세로
		//
		// 11, 12
		// 21, 22
		return Matrix22{
			  ( m1._11 * m2._11 ) + ( m1._12 * m2._21 )    , ( m1._11 * m2._12 ) + ( m1._12 * m2._22 )
			, ( m1._21 * m2._11 ) + ( m1._22 * m2._21 )    , ( m1._21 * m2._12 ) + ( m1._22 * m2._22 )
		};
	}
	inline void operator*=( Matrix22& m1, const Matrix22& m2 )
	{
		m1 = ( m1 * m2 );
	}
	


	inline Matrix22 inverse( const Matrix22& m )
	{
		//
		// # 일반적인 2 x 2 행렬의 역행렬 공식
		//   1. 행렬식(determinant)을 계산
		//   2. 각 원소의 여인수(cofactor)를 이용하여 수반 행렬(adjugate matrix) 생성
		//   3. 수반 행렬을 행렬식으로 나누는 방식
		// 
		//   A = a b    |   A^-1 = 1/det(A) *  d -b
		//       c d    |                     -c  a
		// 
		// # Determinant
		//   det(A) = ( ad - bc )
		//   det(A) == 0 이면 역행렬을 가질 수 없다.
		//

		const float inv_det = ( 1 / ( ( m._11 * m._22 ) - ( m._12 * m._21 ) ) );
		return (
			  r2::epsilon_equal( 0.f, inv_det )
			? Matrix22()
			: Matrix22(
				   m._22 * inv_det, -m._12 * inv_det
				, -m._21 * inv_det,  m._11 * inv_det
			)
		);
	}
}