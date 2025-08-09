//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.07.31 PM.03.15
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_matrix44.hpp"

#include "r2_math.hpp"
#include "r2_matrix33_transform_vector3.hpp"
#include "r2_vector3.hpp"

//
// DX : V x M
// Opengl : M x V
// 무엇을 앞에 두고 곱하냐의 차이가 있기 때문에 이동 행렬등을 만들 때 위치의 차이가 생긴다.
// DX의 경우 41, 42, 43 값을 쓰면 되는데
// OpenGL은 14, 24, 34 값을 쓴다.
//

namespace r2
{
	inline Vector3 operator*( const Matrix44& m, const Vector3& v )
	{
		//
		// 가로 x 세로
		//
		// 11, 12, 13, 14
		// 21, 22, 23, 24
		// 31, 32, 33, 34
		// 41, 42, 43, 44
		//
		// Matrix44 x Vector3
		//  x = ( m._11 * v.x ) + ( m._12 * v.y ) + ( m._13 * v.z ) + ( m._14 * v.w ) <- v.w == 1
		//  y = ( m._21 * v.x ) + ( m._22 * v.y ) + ( m._23 * v.z ) + ( m._24 * v.w ) <- v.w == 1
		//  z = ( m._31 * v.x ) + ( m._32 * v.y ) + ( m._33 * v.z ) + ( m._34 * v.w ) <- v.w == 1
		//  w = ( m._41 * v.x ) + ( m._42 * v.y ) + ( m._43 * v.z ) + ( m._44 * v.w ) <- 이 라인은 필요 없다.
		//

		return Vector3(
			  ( m._11 * v.x ) + ( m._12 * v.y ) + ( m._13 * v.z ) + ( m._14 )
			, ( m._21 * v.x ) + ( m._22 * v.y ) + ( m._23 * v.z ) + ( m._24 )
			, ( m._31 * v.x ) + ( m._32 * v.y ) + ( m._33 * v.z ) + ( m._34 )
		);
	}



	inline Matrix44 build_mat44_translate_vec3( const float x, const float y, const float z )
	{
		//
		//  -,  -,  -,  x
		//  -,  -,  -,  y
		//  -,  -,  -,  z
		//  -,  -,  -,  -
		//

		Matrix44 ret;

		ret._14 = x;
		ret._24 = y;
		ret._34 = z;

		return ret;
	}
	inline Matrix44 build_mat44_translate_vec3( const r2::Vector3 v )
	{
		return build_mat44_translate_vec3( v.x, v.y, v.z );
	}
	inline Matrix44 inverse_mat44_translate_vec3( const r2::Matrix44 m )
	{
		//
		//  -,  -,  -,  -x
		//  -,  -,  -,  -y
		//  -,  -,  -,  -z
		//  -,  -,  -,   -
		//
		Matrix44 ret;

		ret._14 = -m._14;
		ret._24 = -m._24;
		ret._34 = -m._34;

		return ret;
	}



	inline Matrix44 build_mat44_scale_vec3( const float x, const float y, const float z )
	{
		//
		//  x,  -,  -,  -
		//  -,  y,  -,  -
		//  -,  -,  z,  -
		//  -,  -,  -,  -
		//

		Matrix44 ret;

		ret._11 = x;
		ret._22 = y;
		ret._33 = z;

		return ret;
	}
	inline Matrix44 build_mat44_scale_vec3( const r2::Vector3 v )
	{
		return build_mat44_scale_vec3( v.x, v.y, v.z );
	}
	inline Matrix44 inverse_mat44_scale_vec3( const Matrix44& m )
	{
		//
		//  1/x,    -,    -,  -
		//    -,  1/y,    -,  -
		//    -,    -,  1/z,  -
		//    -,    -,    -,  -
		//

		Matrix44 ret;

		ret._11 = ( 1 / m._11 );
		ret._22 = ( 1 / m._22 );
		ret._33 = ( 1 / m._33 );

		return ret;
	}



	//
	// 오른손 좌표계
	// > 축 기준 반시계 방향 회전이 기본
	//
	inline Matrix44 build_mat44_rotation_x_vec3( const r2::Radian radian )
	{
		//
		//  -,  -,  -,  -
		//  -,  c, -s,  -
		//  -,  s,  c,  -
		//  -,  -,  -,  -
		//

		Matrix44 ret;

		// diagonal
		ret._22 = std::cos( radian.Get() );
		ret._33 = std::cos( radian.Get() );

		ret._23 = -std::sin( radian.Get() );
		ret._32 = std::sin( radian.Get() );

		return ret;
	}
	inline Matrix44 build_mat44_rotation_x_vec3( const r2::Degree degree )
	{
		return build_mat44_rotation_x_vec3( r2::deg2rad( degree ) );
	}
	inline Matrix44 build_mat44_rotation_y_vec3( const r2::Radian radian )
	{
		//
		//  c,  -,  s,  -
		//  -,  -,  -,  -
		// -s,  -,  c,  -
		//  -,  -,  -,  -
		//

		Matrix44 ret;

		// diagonal
		ret._11 = std::cos( radian.Get() );
		ret._33 = std::cos( radian.Get() );

		ret._13 = std::sin( radian.Get() );
		ret._31 = -std::sin( radian.Get() );

		return ret;
	}
	inline Matrix44 build_mat44_rotation_y_vec3( const r2::Degree degree )
	{
		return build_mat44_rotation_y_vec3( r2::deg2rad( degree ) );
	}
	inline Matrix44 build_mat44_rotation_z_vec3( const r2::Radian radian )
	{
		//
		//  c, -s,  -,  -
		//  s,  c,  -,  -
		//  -,  -,  -,  -
		//  -,  -,  -,  -
		//

		Matrix44 ret;

		// diagonal
		ret._11 = std::cos( radian.Get() );
		ret._22 = std::cos( radian.Get() );

		ret._12 = -std::sin( radian.Get() );
		ret._21 = std::sin( radian.Get() );

		return ret;
	}
	inline Matrix44 build_mat44_rotation_z_vec3( const r2::Degree degree )
	{
		return build_mat44_rotation_z_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix44 build_mat44_rotation_vec3( const Radian rotation_z, const Radian rotation_y, const Radian rotation_x )
	{
		//
		// Z > Y > X
		//    > 좌/우
		//    > 위/아래 
		//    > 기울임
		// 
		// m = x * y * z
		//
		return (
			  build_mat44_rotation_x_vec3( rotation_x )
			* build_mat44_rotation_y_vec3( rotation_y )
			* build_mat44_rotation_z_vec3( rotation_z )
		);
	}
	inline Matrix44 build_mat44_rotation_vec3( const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x )
	{
		return build_mat44_rotation_vec3( r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x ) );
	}
	inline Matrix44 inverse_mat44_rotation_vec3( const r2::Matrix44 m )
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
		// 11,  21,  31,  -
		// 12,  22,  32,  -
		// 13,  23,  33,  -
		//  -,   -,   -,  1
		//
		return Matrix44(
			  m._11, m._21, m._31, 0
			, m._12, m._22, m._32, 0
			, m._13, m._23, m._33, 0
			,     0,     0,     0, 1
		);
	}



	inline Matrix44 build_mat44_scale_rotation_vec3(
		  const float scale_x, const float scale_y, const float scale_z
		, const Radian rotation_z, const Radian rotation_y, const Radian rotation_x
	)
	{
		//
		// S > Z > Y > X
		//    > 크기
		//    > 좌/우 회전
		//    > 위/아래 회전
		//    > 기울임 회전
		// 
		// m = x * y * z * s
		//
		return (
			  build_mat44_rotation_x_vec3( rotation_x )
			* build_mat44_rotation_y_vec3( rotation_y )
			* build_mat44_rotation_z_vec3( rotation_z )
			* build_mat44_scale_vec3( scale_x, scale_y, scale_z )
		);
	}
	inline Matrix44 build_mat44_scale_rotation_vec3(
		  const r2::Vector3 scale
		, const r2::Radian rotation_z, const r2::Radian rotation_y, const r2::Radian rotation_x
	)
	{
		return build_mat44_scale_rotation_vec3(
			  scale.x, scale.y, scale.z
			, rotation_z , rotation_y, rotation_x
		);
	}
	inline Matrix44 build_mat44_scale_rotation_vec3(
		  const float scale_x, const float scale_y, const float scale_z
		, const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x
	)
	{
		return build_mat44_scale_rotation_vec3(
			  scale_x, scale_y, scale_z
			, r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x )
		);
	}
	inline Matrix44 build_mat44_scale_rotation_vec3(
		  const r2::Vector3 scale
		, const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x
	)
	{
		return build_mat44_scale_rotation_vec3(
			  scale.x, scale.y, scale.z
			, r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x )
		);
	}
	inline Matrix44 inverse_mat44_scale_rotation_vec3( const Matrix44 m )
	{
		const Matrix33 temp = inverse( Matrix33(
			  m._11, m._12, m._13
			, m._21, m._22, m._23
			, m._31, m._32, m._33
		) );
		return Matrix44(
			  temp._11,   temp._12,   temp._13,   0.f
			, temp._21,   temp._22,   temp._23,   0.f
			, temp._31,   temp._32,   temp._33,   0.f
			, 0.f     ,   0.f     ,   0.f     ,   1.f
		);
	}
	


	inline Matrix44 build_mat44_rotation_translate_vec3(
		  const Radian rotation_z, const Radian rotation_y, const Radian rotation_x
		, const float translate_x, const float translate_y, const float translate_z
	)
	{
		//
		// S > Z > Y > X
		//    > 크기
		//    > 좌/우 회전
		//    > 위/아래 회전
		//    > 기울임 회전
		// 
		// m = x * y * z * s
		//
		return (
			  build_mat44_translate_vec3( translate_x, translate_y, translate_z )
			* build_mat44_rotation_x_vec3( rotation_x )
			* build_mat44_rotation_y_vec3( rotation_y )
			* build_mat44_rotation_z_vec3( rotation_z )
		);
	}
	inline Matrix44 build_mat44_rotation_translate_vec3(
		  const r2::Radian rotation_z, const r2::Radian rotation_y, const r2::Radian rotation_x
		, const r2::Vector3 translate
	)
	{
		return build_mat44_rotation_translate_vec3(
			  rotation_y, rotation_x, rotation_z
			, translate.x, translate.y, translate.z
		);
	}
	inline Matrix44 build_mat44_rotation_translate_vec3(
		  const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x
		, const float translate_x, const float translate_y, const float translate_z
	)
	{
		return build_mat44_rotation_translate_vec3(
			  r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x )
			, translate_x, translate_y, translate_z
		);
	}
	inline Matrix44 build_mat44_rotation_translate_vec3(
		  const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x
		, const r2::Vector3 translate
	)
	{
		return build_mat44_rotation_translate_vec3(
			  r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x )
			, translate.x, translate.y, translate.z
		);
	}
	inline Matrix44 inverse_mat44_rotation_translate_vec3( const Matrix44 m )
	{
		//
		// M =  R, T    |    iM = iR, -( iR * T )
		//      0, 1    |          0,           1
		//
		//
		// iR = 순수 회전 행렬은 전치로 역행렬 생성 가능
		//
		const Matrix33 inverse_r(
			  m._11, m._21, m._31
			, m._12, m._22, m._32
			, m._13, m._23, m._33
		);

		const r2::Vector3 inverse_t = -( inverse_r * Vector3( m._14, m._24, m._34 ) );

		return Matrix44(
			  inverse_r._11,   inverse_r._12,   inverse_r._13,   inverse_t.x
			, inverse_r._21,   inverse_r._22,   inverse_r._23,   inverse_t.y
			, inverse_r._31,   inverse_r._32,   inverse_r._33,   inverse_t.z
			, 0.f          ,             0.f,             0.f,           1.f
		);
	}



	inline Matrix44 build_mat44_scale_rotation_translate_vec3(
		  const float scale_x, const float scale_y, const float scale_z
		, const r2::Radian rotation_z, const r2::Radian rotation_y, const r2::Radian rotation_x
		, const float translate_x, const float translate_y, const float translate_z
	)
	{
		// scale > rotation > translate
		// translate * rotation * scale
		return( 
			  build_mat44_translate_vec3( translate_x, translate_y, translate_z )
			* build_mat44_rotation_x_vec3( rotation_x )
			* build_mat44_rotation_y_vec3( rotation_y )
			* build_mat44_rotation_z_vec3( rotation_z )
			* build_mat44_scale_vec3( scale_x, scale_y, scale_z )
		);
	}
	inline Matrix44 build_mat44_scale_rotation_translate_vec3(
		  const float scale_x, const float scale_y, const float scale_z
		, const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x
		, const float translate_x, const float translate_y, const float translate_z
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale_x, scale_y, scale_z
			, r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x )
			, translate_x, translate_y, translate_z
		);
	}
	inline Matrix44 build_mat44_scale_rotation_translate_vec3(
		  const r2::Vector3 scale
		, const r2::Radian rotation_z, const r2::Radian rotation_y, const r2::Radian rotation_x
		, const r2::Vector3 translate
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale.x, scale.y, scale.z
			, rotation_z, rotation_y, rotation_x
			, translate.x, translate.y, translate.z
		);
	}
	inline Matrix44 build_mat44_scale_rotation_translate_vec3(
		  const r2::Vector3 scale
		, const r2::Degree rotation_z, const r2::Degree rotation_y, const r2::Degree rotation_x
		, const r2::Vector3 translate
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale.x, scale.y, scale.z
			, r2::deg2rad( rotation_z ), r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x )
			, translate.x, translate.y, translate.z
		);
	}
	inline Matrix44 inverse_mat44_scale_rotation_translate_vec3( const Matrix44 m )
	{
		//
		// M = SR, T    |    iM = iSR, -( iSR * T )
		//      0, 1    |           0,            1
		//
		//
		// iSR = Matrix33의 역행렬 생성 로직 사용
		// 
		// -( iSR * T ) = 
		//

		const Matrix33 inverse_sr = inverse( Matrix33(
			  m._11, m._12, m._13
			, m._21, m._22, m._23
			, m._31, m._32, m._33
		) );

		const r2::Vector3 inverse_t = -( inverse_sr * Vector3( m._14, m._24, m._34 ) );

		return Matrix44(
			  inverse_sr._11, inverse_sr._12, inverse_sr._13, inverse_t.x
			, inverse_sr._21, inverse_sr._22, inverse_sr._23, inverse_t.y
			, inverse_sr._31, inverse_sr._32, inverse_sr._33, inverse_t.z
			,            0.f,            0.f,            0.f,         1.f
		);
	}



	inline Matrix44 build_mat44_lookat_vec3( const r2::Vector3& position, const r2::Vector3& target, const r2::Vector3& up )
	{
		const r2::Vector3 z_axis = r2::normalize( target - position );
		const r2::Vector3 x_axis = r2::normalize( r2::cross( up, z_axis ) );
		const r2::Vector3 y_axis = r2::cross( z_axis, x_axis );

		return Matrix44{
			  x_axis.x    , y_axis.x    , z_axis.x    , 0
			, x_axis.y    , y_axis.y    , z_axis.y    , 0
			, x_axis.z    , y_axis.z    , z_axis.z    , 0
			, 0           , 0           , 0           , 1
		};
	}



	inline r2::Radian extract_mat44_euler_z_vec3( const r2::Matrix44& m )
	{
		return extract_mat33_euler_z_vec3( Matrix33(
			  m._11, m._12, m._13
			, m._21, m._22, m._23
			, m._31, m._32, m._33
		) );
	}
	inline r2::Radian extract_mat44_euler_y_vec3( const r2::Matrix44& m )
	{
		return extract_mat33_euler_y_vec3( Matrix33(
			  m._11, m._12, m._13
			, m._21, m._22, m._23
			, m._31, m._32, m._33
		) );
	}
	inline r2::Radian extract_mat44_euler_x_vec3( const r2::Matrix44& m )
	{
		return extract_mat33_euler_x_vec3( Matrix33(
			  m._11, m._12, m._13
			, m._21, m._22, m._23
			, m._31, m._32, m._33
		) );
	}
}