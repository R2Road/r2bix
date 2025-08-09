#pragma once

#include <iomanip>
#include <iostream>

#include "r2_NoneCopyable.h"
#include "r2_degree.hpp"

inline std::ostream& operator<<( std::ostream& o, const r2::Degree& degree )
{
	static const int w = 10;

	return o
		<< std::left

		<< degree.Get()

		<< std::right;
}

namespace r2helper
{
	class STDPrinter_Degree : private r2::NoneCopyable
	{
	private:
		STDPrinter_Degree() = delete;

	public:
		inline static void Print( const r2::Degree& degree )
		{
			std::cout
				<< "\t"

				<< "Degree" "   "

				<< degree

				<< "\n"
			;
		}
	};
}