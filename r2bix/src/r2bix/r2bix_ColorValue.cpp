#pragma once
#include "r2bix_ColorValue.h"

namespace r2bix
{
	unsigned char GetForegroundColor( const ColorValue color_value )
	{
		static const uint8_t mask = ( static_cast<uint8_t>( -1 ) >> 4 );
		return color_value & mask;
	}
	unsigned char GetBackgroundColor( const ColorValue color_value )
	{
		static const uint8_t mask = ( ( static_cast<uint8_t>( -1 ) >> 4 ) << 4 );
		return color_value & mask;
	}
}