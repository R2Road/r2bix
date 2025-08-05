//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.08.01 PM.11.30
// # Version			: 1.0.0.0
//

#pragma once

#include "r2_matrix44_transform_vector3.hpp"
#include "r2_vector4.hpp"

namespace r2
{
	inline Vector4 operator*( const Matrix44& m, const Vector4& v )
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



	inline Matrix44 build_mat44_translate_vec4( const float translate_x, const float translate_y, const float translate_z )
	{
		return build_mat44_translate_vec3( translate_x, translate_y, translate_z );
	}
	inline Matrix44 build_mat44_translate_vec4( const r2::Vector4 v )
	{
		return build_mat44_translate_vec3( v.x, v.y, v.z );
	}
	inline Matrix44 inverse_mat44_translate_vec4( const r2::Matrix44 m )
	{
		return inverse_mat44_translate_vec3( m );
	}



	inline Matrix44 build_mat44_scale_vec4( const float scale_x, const float scale_y, const float scale_z )
	{
		return build_mat44_scale_vec3( scale_x, scale_y, scale_z );
	}
	inline Matrix44 build_mat44_scale_vec4( const r2::Vector4 v )
	{
		return build_mat44_scale_vec3( v.x, v.y, v.z );
	}
	inline Matrix44 inverse_mat44_scale_vec4( const Matrix44& m )
	{
		return inverse_mat44_scale_vec3( m );
	}



	//
	// 오른손 좌표계
	// > 축 기준 반시계 방향 회전이 기본
	//
	inline Matrix44 build_mat44_rotation_x_vec4( const r2::Radian radian )
	{
		return build_mat44_rotation_x_vec3( radian );
	}
	inline Matrix44 build_mat44_rotation_x_vec4( const r2::Degree degree )
	{
		return build_mat44_rotation_x_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix44 build_mat44_rotation_y_vec4( const r2::Radian radian )
	{
		return build_mat44_rotation_y_vec3( radian );
	}
	inline Matrix44 build_mat44_rotation_y_vec4( const r2::Degree degree )
	{
		return build_mat44_rotation_y_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix44 build_mat44_rotation_z_vec4( const r2::Radian radian )
	{
		return build_mat44_rotation_z_vec3( radian );
	}
	inline Matrix44 build_mat44_rotation_z_vec4( const r2::Degree degree )
	{
		return build_mat44_rotation_z_vec3( r2::deg2rad( degree ) );
	}

	inline Matrix44 build_mat44_rotation_vec4( const Radian rotation_y, const Radian rotation_x, const Radian rotation_z )
	{
		return build_mat44_rotation_vec3( rotation_z, rotation_x, rotation_y );
	}
	inline Matrix44 build_mat44_rotation_vec4( const r2::Degree rotation_y, const r2::Degree rotation_x, const r2::Degree rotation_z )
	{
		return build_mat44_rotation_vec3( r2::deg2rad( rotation_y ), deg2rad( rotation_x ), deg2rad( rotation_z ) );
	}
	inline Matrix44 inverse_mat44_rotation_vec4( const r2::Matrix44 m )
	{
		return inverse_mat44_rotation_vec3( m );
	}
	


	inline Matrix44 build_mat44_scale_rotation_translate_vec4(
		  const float scale_x, const float scale_y, const float scale_z
		, const r2::Radian rotation_y, const r2::Radian rotation_x, const r2::Radian rotation_z
		, const float translate_x, const float translate_y, const float translate_z
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale_x, scale_y, scale_z
			, rotation_y, rotation_x, rotation_z
			, translate_x, translate_y, translate_z
		);
	}
	inline Matrix44 build_mat44_scale_rotation_translate_vec4(
		  const float scale_x, const float scale_y, const float scale_z
		, const r2::Degree rotation_y, const r2::Degree rotation_x, const r2::Degree rotation_z
		, const float translate_x, const float translate_y, const float translate_z
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale_x, scale_y, scale_z
			, r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x ), r2::deg2rad( rotation_z )
			, translate_x, translate_y, translate_z
		);
	}
	inline Matrix44 build_mat44_scale_rotation_translate_vec4(
		  const r2::Vector4 scale
		, const r2::Radian rotation_y, const r2::Radian rotation_x, const r2::Radian rotation_z
		, const r2::Vector4 translate
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale.x, scale.y, scale.z
			, rotation_y, rotation_x, rotation_z
			, translate.x, translate.y, translate.z
		);
	}
	inline Matrix44 build_mat44_scale_rotation_translate_vec4(
		  const r2::Vector4 scale
		, const r2::Degree rotation_y, const r2::Degree rotation_x, const r2::Degree rotation_z
		, const r2::Vector4 translate
	)
	{
		return build_mat44_scale_rotation_translate_vec3(
			  scale.x, scale.y, scale.z
			, r2::deg2rad( rotation_y ), r2::deg2rad( rotation_x ), r2::deg2rad( rotation_z )
			, translate.x, translate.y, translate.z
		);
	}
	inline Matrix44 inverse_mat44_scale_rotation_translate_vec4( const Matrix44 m )
	{
		return inverse_mat44_scale_rotation_translate_vec3( m );
	}
}