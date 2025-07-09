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

#include "r2_Matrix4.h"

namespace r2
{
	inline Matrix4 BuildMatrix4_ViewTransform(
		  const r2::Vector4 init_eye
		, const r2::Vector4 init_center
		, const r2::Vector4 init_up
	)
	{
		const r2::Vector4 cam_forward = r2::normalize( init_eye - init_center );
		const r2::Vector4 cam_right = r2::normalize( r2::cross( init_up, cam_forward ) );
		const r2::Vector4 cam_up = r2::cross( cam_forward, cam_right );

		return Matrix4{
			  cam_right.x		, cam_right.y		, cam_right.z		, -r2::dot( cam_right, init_eye )
			, cam_up.x			, cam_up.y			, cam_up.z			, -r2::dot( cam_up, init_eye )
			, cam_forward.x		, cam_forward.y		, cam_forward.z		, -r2::dot( cam_forward, init_eye )
			, 0.f				, 0.f				, 0.f				, 1.f
		};
	}

	inline Matrix4 BuildMatrix4_ProjectionTransform_OrthographicZ01(
		  const float left
		, const float right
		, const float bottom
		, const float top
		, const float near
		, const float far
	)
	{
		return r2::Matrix4(
			  2 / ( right - left )	, 0.f					, 0.f				, -( right + left ) / ( right - left )
			, 0.f					, 2 / ( top - bottom )	, 0.f				, -( top + bottom ) / ( top - bottom )
			, 0.f					, 0.f					, 1 / ( far - near)	, -near / ( far - near)
			, 0.f					, 0.f					, 0.f				, 1.f
		);
	}

	inline Matrix4 BuildMatrix4_ViewportTransform_ZM1P1(
		  const int viewport_w
		, const int viewport_h
		, const float near
		, const float far
	)
	{
		return Matrix4{
			viewport_w / 2.f	, 0.f				, 0.f					, viewport_w / 2.f
			, 0.f				, viewport_h / 2.f	, 0.f					, viewport_h / 2.f
			, 0.f				, 0.f				, ( far - near ) / 2.f	, ( near + far) / 2.f
			, 0.f				, 0.f				, 0.f					, 1.f
		};
	}
}