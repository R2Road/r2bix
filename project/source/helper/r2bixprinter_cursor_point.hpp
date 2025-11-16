#pragma once

#include <iomanip>
#include <iostream>

#include "r2_none_copyable.hpp"

#include "r2bix_input_Constant.h"

inline std::ostream& operator<<( std::ostream& o, const r2bix_input::CursorPoint& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "\t"

		<< "x : " << std::setw( w ) << v.GetX()

		<< "   "

		<< "y : " << std::setw( w ) << v.GetY()

		<< std::right
	;
}

namespace r2bixprinter
{
	class R2bix_CursorPoint : private r2::NoneCopyable
	{
	private:
		R2bix_CursorPoint() = delete;

	public:
		template<typename T>
		inline static void Print( const r2bix_input::CursorPoint& v )
		{
			std::cout
				<< "\t" "Cursor Point"

				<< v

				<< "\n";
		}
	};
}