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

#include "r2_matrix33.hpp"

#include "r2_math.hpp"
#include "r2_vector2.hpp"

namespace r2
{
	inline Vector2 operator*( const Matrix33& m, const Vector2& v )
	{
		//
		// Matrix33 x Vector3
		//  x = ( m._11 * v.x ) + ( m._12 * v.y ) + ( m._13 * v.z ) <- v.z == 1
		//  y = ( m._21 * v.x ) + ( m._22 * v.y ) + ( m._23 * v.z ) <- v.z == 1
		//  z = ( m._31 * v.x ) + ( m._32 * v.y ) + ( m._33 * v.z ) <- 이 라인은 필요 없다.
		//
		return Vector2(
			  ( m._11 * v.x ) + ( m._12 * v.y ) + ( m._13 )
			, ( m._21 * v.x ) + ( m._22 * v.y ) + ( m._23 )
		);
	}



	inline Matrix33 build_mat33_translate_vec2( const float translate_x, const float translate_y )
	{
		//
		//  -,  -,  x
		//  -,  -,  y
		//  -,  -,  -
		//

		Matrix33 ret;

		ret._13 = translate_x;
		ret._23 = translate_y;

		return ret;
	}
	inline Matrix33 build_mat33_translate_vec2( const r2::Vector2 translate )
	{
		return build_mat33_translate_vec2( translate.x, translate.y );
	}
	inline Matrix33 inverse_mat33_translate_vec2( const Matrix33& m )
	{
		//
		//  -,  -,  -x
		//  -,  -,  -y
		//  -,  -,   -
		//
		Matrix33 ret;

		ret._13 = -m._13;
		ret._23 = -m._23;

		return ret;
	}




	inline Matrix33 build_mat33_scale_vec2( const float scale_x, const float scale_y )
	{
		//
		//  x,  -,  -
		//  -,  y,  -
		//  -,  -,  -
		//

		Matrix33 ret;

		ret._11 = scale_x;
		ret._22 = scale_y;

		return ret;
	}
	inline Matrix33 inverse_mat33_scale_vec2( const Matrix33& m )
	{
		//
		//  1/x,   -,  -
		//  -,   1/y,  -
		//  -,     -,  -
		//

		Matrix33 ret;

		ret._11 = ( 1 / m._11 );
		ret._22 = ( 1 / m._22 );

		return ret;
	}



	//
	// 오른손 좌표계
	// > 축 기준 반시계 방향 회전이 기본
	//
	inline Matrix33 build_mat33_rotation_vec2( const r2::Radian radian )
	{
		//
		//  c, -s,  -
		//  s,  c,  -
		//  -,  -,  -
		//

		Matrix33 ret;

		ret._11 = std::cos( radian.Get() );   ret._12 = -std::sin( radian.Get() );
		ret._21 = std::sin( radian.Get() );   ret._22 =  std::cos( radian.Get() );

		return ret;
	}
	inline Matrix33 build_mat33_rotation_vec2( const r2::Degree degree )
	{
		return build_mat33_rotation_vec2( r2::deg2rad( degree ) );
	}
	inline Matrix33 inverse_mat33_rotation_vec2( const Matrix33& m )
	{
		//
		// 2 x 2 회전 구간 : 전치
		//
		// 11, 21, -
		// 12, 22, -
		//  -,  -, -

		Matrix33 ret;

		ret._11 = m._11;    ret._12 = m._21;
		ret._21 = m._12;    ret._22 = m._22;

		return ret;
	}



	inline Matrix33 build_mat33_rotation_translate_vec2( const r2::Radian radian, const float translate_x, const float translate_y )
	{
		// rotation > translate
		return build_mat33_translate_vec2( translate_x, translate_y ) * build_mat33_rotation_vec2( radian );
	}
	inline Matrix33 build_mat33_rotation_translate_vec2( const r2::Radian radian, const r2::Vector2 translate )
	{
		return build_mat33_rotation_translate_vec2( radian, translate.x, translate.y );
	}
	inline Matrix33 build_mat33_rotation_translate_vec2( const r2::Degree degree, const float translate_x, const float translate_y )
	{
		return build_mat33_rotation_translate_vec2( r2::deg2rad( degree ), translate_x , translate_y );
	}
	inline Matrix33 build_mat33_rotation_translate_vec2( const r2::Degree degree, const r2::Vector2 translate )
	{
		return build_mat33_rotation_translate_vec2( r2::deg2rad( degree ), translate.x, translate.y );
	}
	inline Matrix33 inverse_mat33_rotation_translate_vec2( const Matrix33& m )
	{
		//
		// 2 x 2 회전 구간 : 전치
		// 이동 구간 : 역회전 + (-)
		//
		// 11, 21,   -(  ( x * cos ) + ( y * sin ) )
		// 12, 22,   -( -( x * sin ) + ( y * cos ) )
		// -,   -,    -

		Matrix33 ret;

		ret._11 = m._11;    ret._12 = m._21;    ret._13 = -( (  m._13 * m._11 ) + ( m._23 * m._21 ) ); // m._11 = cos, m._21 = sin
		ret._21 = m._12;    ret._22 = m._22;	ret._23 = -( ( -m._13 * m._21 ) + ( m._23 * m._11 ) );

		return ret;
	}



	inline Matrix33 build_mat33_scale_rotation_translate_vec2( const float scale_x, const float scale_y, const r2::Radian radian, const float translate_x, const float translate_y )
	{
		// scale > rotation > translate
		// translate * rotation * scale
		return build_mat33_translate_vec2( translate_x, translate_y ) * build_mat33_rotation_vec2( radian ) * build_mat33_scale_vec2( scale_x, scale_y );
	}
	inline Matrix33 build_mat33_scale_rotation_translate_vec2( const float scale_x, const float scale_y, const r2::Degree degree, const float translate_x, const float translate_y )
	{
		return build_mat33_scale_rotation_translate_vec2( scale_x, scale_y, r2::deg2rad( degree ), translate_x, translate_y );
	}
	inline Matrix33 build_mat33_scale_rotation_translate_vec2( const r2::Vector2 scale, const r2::Radian radian, const r2::Vector2 translate )
	{
		return build_mat33_scale_rotation_translate_vec2( scale.x, scale.y, radian, translate.x, translate.y );
	}
	inline Matrix33 build_mat33_scale_rotation_translate_vec2( const r2::Vector2 scale, const r2::Degree degree, const r2::Vector2 translate )
	{
		return build_mat33_scale_rotation_translate_vec2( scale.x, scale.y, r2::deg2rad( degree ), translate.x, translate.y );
	}
	inline Matrix33 inverse_mat33_scale_rotation_translate_vec2( const Matrix33& m )
	{
		//
		// M = SR, T     |    I = iSR, -( iSR * T )
		//      0, 1     |          0,            1
		//
		// 
		// iSR = 2 x 2 : 회전 * scale 구간 : Matrix22의 inverse 와 동일
		// 
		// -( iSR * T ) : 회전후 이동의 반대 처리 : 회전된 축을 기준으로 역 이동
		//

		Matrix33 ret;

		const float inv_det = ( 1 / ( ( m._11 * m._22 ) - ( m._12 * m._21 ) ) );
		if( r2::epsilon_equal( 0.f, inv_det ) )
		{
			return ret;
		}

		// iSR : Inverse Scale * Rotation
		ret = Matrix33(
			   m._22 * inv_det,    -m._12 * inv_det,    0.f
			, -m._21 * inv_det,     m._11 * inv_det,    0.f
			,              0.f,                 0.f,    1.f
		);

		// -( iSR * T ) : Matrix22 * Vector2 : 회전된 축을 기준으로 역 이동
		ret._13 = -( ( ret._11 * m._13 ) + ( ret._12 * m._23 ) );
		ret._23 = -( ( ret._21 * m._13 ) + ( ret._22 * m._23 ) );

		return ret;
	}
}