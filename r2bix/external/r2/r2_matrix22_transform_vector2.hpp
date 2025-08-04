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

#include "r2_matrix22.hpp"

#include "r2_math.hpp"
#include "r2_vector2.hpp"

namespace r2
{
	inline Vector2 operator*( const Matrix22& m, const Vector2& v )
	{
		//
		// 가로 x 세로
		//
		// 11, 12
		// 21, 22
		return Vector2{
			  ( m._11 * v.x ) + ( m._12 * v.y )
			, ( m._21 * v.x ) + ( m._22 * v.y )
		};
	}



	inline Matrix22 build_mat22_scale_vec2( const float scale_x, const float scale_y )
	{
		//
		//  x,  -
		//  -,  y
		//

		Matrix22 ret;

		ret._11 = scale_x;
		ret._22 = scale_y;

		return ret;
	}
	inline Matrix22 inverse_mat22_scale_vec2( const Matrix22& m )
	{
		//
		//  1/x,  -
		//    -,  1/y
		//
		return Matrix22(
			  1/m._11  , m._21
			, m._12    , 1/m._22
		);
	}


	//
	// 오른손 좌표계
	// > 축 기준 반시계 방향 회전이 기본
	//
	inline Matrix22 build_mat22_rotation_vec2( const r2::Radian radian )
	{
		//
		//  c, -s
		//  s,  c
		//

		Matrix22 ret;

		ret._11 = std::cos( radian.Get() );    ret._12 = -std::sin( radian.Get() );
		ret._21 = std::sin( radian.Get() );    ret._22 = std::cos( radian.Get() );

		return ret;
	}
	inline Matrix22 build_mat22_rotation_vec2( const r2::Degree degree )
	{
		return build_mat22_rotation_vec2( r2::deg2rad( degree ) );
	}
	inline Matrix22 inverse_mat22_rotation_vec2( const Matrix22& m )
	{
		//
		// 2 x 2 회전 구간 : 전치
		//
		// 11, 21
		// 12, 22
		return Matrix22(
			  m._11, m._21
			, m._12, m._22
		);
	}
}