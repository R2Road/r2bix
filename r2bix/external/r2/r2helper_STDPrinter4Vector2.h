#pragma once

#include <iomanip>
#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Vector2.h"

inline std::ostream& operator<<( std::ostream& o, const r2::Vector2& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "\t"

		<< "   "
		"x : " << std::setw( w ) << v.x
		<< "   "
		"y : " << std::setw( w ) << v.y

		<< std::right;
}

namespace r2helper
{
	class STDPrinter4Vector2 : private r2::NoneCopyable
	{
	private:
		STDPrinter4Vector2() = delete;

	public:
		inline static void Print( const r2::Vector2& v )
		{
			std::cout
				<< std::left

				<< "\t" "Vector2"

				<< v

				<< "\n"

				<< std::right;
		}
	};
}