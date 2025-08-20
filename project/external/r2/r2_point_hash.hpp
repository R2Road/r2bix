#pragma once

#include "r2_point.hpp"

namespace r2
{
	struct PointHash
	{
		template<typename T>
		std::size_t operator()( const r2::Point<T>& point ) const
		{ 
			return ( ( point.GetY() * 10000 ) + point.GetX() );
		}
	};
}