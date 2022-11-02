#pragma once

#include <stdint.h>

namespace r2bix_input
{
	using KeyCodeTypeT = uint8_t;

	int GetKeyState( const KeyCodeTypeT key_code );
	bool HasWindowFocus();
}