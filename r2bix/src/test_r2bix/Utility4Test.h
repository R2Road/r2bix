#pragma once

#include "r2/r2_RectInt.h"

namespace r2utility
{
	class Utility
	{
	private:
		Utility() = delete;

	public:
		static void DrawRect( const int offset_y, const r2::RectInt& rect, const char c );
	};
}