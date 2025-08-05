//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.05 PM.06.40
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_matrix33.hpp"

#include "r2_math.hpp"
#include "r2_vector3.hpp"

namespace r2
{
	inline Vector3 operator*( const Matrix33& m, const Vector3& v )
	{
		//
		// 가로 x 세로
		//
		// 11, 12, 13
		// 21, 22, 23
		// 31, 32, 33
		return Vector3{
			  ( m._11 * v.x ) + ( m._12 * v.y ) + ( m._13 * v.z )
			, ( m._21 * v.x ) + ( m._22 * v.y ) + ( m._23 * v.z )
			, ( m._31 * v.x ) + ( m._32 * v.y ) + ( m._33 * v.z )
		};
	}



	inline Matrix33 build_mat33_scale_vec3( const float scale_x, const float scale_y, const float scale_z )
	{
		//
		//  x,  -,  -
		//  -,  y,  -
		//  -,  -,  -
		//

		Matrix33 ret;

		ret._11 = scale_x;
		ret._22 = scale_y;
		ret._33 = scale_z;

		return ret;
	}
	inline Matrix33 inverse_mat33_scale_vec3( const Matrix33& m )
	{
		//
		//  1/x,   -,   -
		//    -, 1/y,   -
		//    -,   -, 1/z
		//

		Matrix33 ret;

		ret._11 = ( 1 / m._11 );
		ret._22 = ( 1 / m._22 );
		ret._33 = ( 1 / m._33 );

		return ret;
	}



	//
	// 오른손 좌표계
	// > 축 기준 반시계 방향 회전이 기본
	//
	inline Matrix33 build_mat33_rotation_x_vec3( const r2::Radian radian )
	{
		//
		//  -,  -,  -
		//  -,  c, -s
		//  -,  s,  c
		//

		Matrix33 ret;

		ret._22 = std::cos( radian.Get() );    ret._23 = -std::sin( radian.Get() );
		ret._32 = std::sin( radian.Get() );    ret._33 =  std::cos( radian.Get() );

		return ret;
	}
	inline Matrix33 build_mat33_rotation_x_vec3( const r2::Degree degree )
	{
		return build_mat33_rotation_x_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix33 build_mat33_rotation_y_vec3( const r2::Radian radian )
	{
		//
		//  c,  -,  s
		//  -,  -,  -
		// -s,  -,  c
		//

		Matrix33 ret;

		ret._11 =  std::cos( radian.Get() );    ret._13 = std::sin( radian.Get() );
		ret._31 = -std::sin( radian.Get() );    ret._33 = std::cos( radian.Get() );

		return ret;
	}
	inline Matrix33 build_mat33_rotation_y_vec3( const r2::Degree degree )
	{
		return build_mat33_rotation_y_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix33 build_mat33_rotation_z_vec3( const r2::Radian radian )
	{
		//
		//  c, -s,  -
		//  s,  c,  -
		//  -,  -,  -
		//

		Matrix33 ret;

		ret._11 = std::cos( radian.Get() );    ret._12 = -std::sin( radian.Get() );
		ret._21 = std::sin( radian.Get() );    ret._22 =  std::cos( radian.Get() );

		return ret;
	}
	inline Matrix33 build_mat33_rotation_z_vec3( const r2::Degree degree )
	{
		return build_mat33_rotation_z_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix33 build_mat33_rotation_vec3( const Radian rotation_y, const Radian rotation_x, const Radian rotation_z )
	{
		//
		// Y > X > Z
		//    > 좌/우
		//    > 위/아래 
		//    > 기울임
		// 
		// m = z * y * x
		//
		return (
			  build_mat33_rotation_z_vec3( rotation_z )
			* build_mat33_rotation_x_vec3( rotation_x )
			* build_mat33_rotation_y_vec3( rotation_y )
		);
	}
	inline Matrix33 build_mat33_rotation_vec3( const r2::Degree rotation_y, const r2::Degree rotation_x, const r2::Degree rotation_z )
	{
		return build_mat33_rotation_vec3( r2::deg2rad( rotation_y ), deg2rad( rotation_x ), deg2rad( rotation_z ) );
	}
	inline Matrix33 inverse_mat33_rotation_vec3( const r2::Matrix33 m )
	{
		//
		// 순수한 회전행렬은 "직교행렬" 특성을 가진다.
		// 직교 행렬은 아래의 조건을 만족한다.
		//     > M * MT == MT * M
		//         > M = 행렬
		//         > MT = 전치 행렬
		// 위의 조건에서 아래의 결론을 이끌어 낼 수 있다.
		//     > MT == iM
		//         > iM = 역행렬
		//
		// 전치
		// 11,  21,  31
		// 12,  22,  32
		// 13,  23,  33
		//
		return Matrix33(
			  m._11, m._21, m._31
			, m._12, m._22, m._32
			, m._13, m._23, m._33
		);
	}



	inline Matrix33 build_mat33_scale_rotation_vec3(
		  const float scale_x, const float scale_y, const float scale_z
		, const Radian rotation_y, const Radian rotation_x, const Radian rotation_z
	)
	{
		//
		// S > Y > X > Z
		//    > 크기
		//    > 좌/우 회전
		//    > 위/아래 회전
		//    > 기울임 회전
		// 
		// m = z * y * x * s
		//
		return (
			  build_mat33_rotation_z_vec3( rotation_z )
			* build_mat33_rotation_x_vec3( rotation_x )
			* build_mat33_rotation_y_vec3( rotation_y )
			* build_mat33_scale_vec3( scale_x, scale_y, scale_z )
		);
	}
	inline Matrix33 build_mat33_scale_rotation_vec3(
		  const float scale_x, const float scale_y, const float scale_z
		, const r2::Degree rotation_y, const r2::Degree rotation_x, const r2::Degree rotation_z
	)
	{
		return build_mat33_scale_rotation_vec3(
			  scale_x, scale_y, scale_z
			, r2::deg2rad( rotation_y ), deg2rad( rotation_x ), deg2rad( rotation_z )
		);
	}



	inline Matrix33 build_mat33_lookat_vec3( const r2::Vector3& position, const r2::Vector3& target, const r2::Vector3& up )
	{
		const r2::Vector3 z_axis = r2::normalize( target - position );
		const r2::Vector3 x_axis = r2::normalize( r2::cross( up, z_axis ) );
		const r2::Vector3 y_axis = r2::cross( z_axis, x_axis );

		return Matrix33{
			  x_axis.x    , y_axis.x    , z_axis.x
			, x_axis.y    , y_axis.y    , z_axis.y
			, x_axis.z    , y_axis.z    , z_axis.z
		};
	}
}