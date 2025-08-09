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

#include "r2_degree.hpp"
#include "r2_radian.hpp"

namespace r2
{

	constexpr double PI = 3.14159265358979323846;
	constexpr Radian R_PI( static_cast<float>( PI ) );
	constexpr Radian R_2PI( R_PI * 2 );
	constexpr Radian R_PI_2( R_PI / 2 );
	constexpr Radian R_PI_4( R_PI / 4 );
	constexpr Radian R_PI_180( R_PI / 180.f );

	constexpr double SA = 180; // Straight Angle
	constexpr Radian D_180( static_cast<float>( SA ) );
	constexpr Radian D_180_PI( D_180 / static_cast<float>( PI ) );

	inline constexpr Radian deg2rad( const Degree degree )
	{
		return Radian( degree.Get() * R_PI_180.Get() );
	}

	inline constexpr Degree rad2deg( const Radian radian )
	{
		return Degree( radian.Get() * D_180_PI.Get() );
	}

}