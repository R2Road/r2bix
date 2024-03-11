#pragma once

#include <stdint.h>
#include "r2/r2_PointInt.h"

namespace r2bix_input
{
	using KeyCodeTypeT = uint8_t;
	int GetKeyState( const KeyCodeTypeT key_code );

	using CursorPoint = r2::PointInt;
	CursorPoint GetCursorPoint();

	bool HasWindowFocus();
}