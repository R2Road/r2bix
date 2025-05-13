#pragma once

#include "r2_Point.h"

namespace r2
{
	struct Hash4Point
	{
		template<typename T>
		std::size_t operator()( const r2::Point<T>& point ) const
		{ 
			return ( ( point.GetY() * 10000 ) + point.GetX() );
		}
	};
}