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

#include "r2_Degree.h"
#include "r2_Radian.h"

namespace r2
{

	inline Radian deg2rad( const Degree degree )
	{
		static const float t = R_PI / 180.f;
		return Radian( degree.Get() * t );
	}

	inline Degree rad2deg( const Radian radian )
	{
		static const float t = 180.f / R_PI;
		return Degree( radian.Get() * t );
	}

}