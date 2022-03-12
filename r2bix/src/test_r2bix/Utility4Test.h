#pragma once

#include "r2/r2_RectInt.h"

class Utility4Test
{
private:
	Utility4Test() = delete;

public:
	static void DrawRect( const int offset_y, const r2::RectInt& rect, const char c );
};