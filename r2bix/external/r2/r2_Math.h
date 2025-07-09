//
// # Version Rule
// - 1.0.0.0 : 사용 가능
// - 0.1.0.0 : 기능 추가/삭제
// - 0.0.1.0 : 기능 개선/변경
// - 0.0.0.1 : 자잘한 변화
//
// # Last Update		: 2025.06.09 PM.10.00
// # Version			: 1.0.0.0
//

#pragma once

//
// _USE_MATH_DEFINES 전처리기는 표준이 아니다.
//
// <numbers> : C++20
//
#define _USE_MATH_DEFINES
#include <math.h>

const float R_PI = static_cast<float>( M_PI );
const float R_2PI = R_PI * 2;
const float R_PI_2 = static_cast<float>( M_PI_2 );
const float R_PI_4 = static_cast<float>( M_PI_4 );

namespace r2
{

	inline float deg2rad( const float degree )
	{
		static const float t = R_PI / 180.f;
		return ( degree * t );
	}

	inline float rad2deg( const float radian )
	{
		static const float t = 180.f / R_PI;
		return ( radian * t );
	}

}