//
// # Version Rule
// - 1.0.0.0 : ��� ����
// - 0.1.0.0 : ��� �߰�/����
// - 0.0.1.0 : ��� ����/����
// - 0.0.0.1 : ������ ��ȭ
//
// # Last Update		: 2025.06.09 PM.10.00
// # Version			: 1.0.0.0
//

#pragma once

//
// _USE_MATH_DEFINES ��ó����� ǥ���� �ƴϴ�.
//
// <numbers> : C++20
//
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>

namespace r2
{
	const float epsilon = 0.00001f;

	inline bool epsilon_equal( const float v1, const float v2 )
	{
		return ( epsilon > std::abs( v1 - v2 ) );
	}
}