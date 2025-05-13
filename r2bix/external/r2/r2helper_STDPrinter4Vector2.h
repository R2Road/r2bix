#pragma once

#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Vector2.h"

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
				<< "\t" "Vector2"

				<< "      "
				   "x : " << v.x
				<< "      "
				   "y : " << v.y

				<< "\n";
		}
	};
}

inline std::ostream& operator<<( std::ostream& o, const r2::Vector2& v )
{
	return o << v.x << "   " << v.y;
}