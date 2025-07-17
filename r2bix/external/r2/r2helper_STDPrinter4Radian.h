#pragma once

#include <iomanip>
#include <iostream>

#include "r2_NoneCopyable.h"
#include "r2_Radian.h"

inline std::ostream& operator<<( std::ostream& o, const r2::Radian& radian )
{
	static const int w = 10;

	return o
		<< std::left

		<< radian.Get()

		<< std::right;
}

namespace r2helper
{
	class STDPrinter4Radian : private r2::NoneCopyable
	{
	private:
		STDPrinter4Radian() = delete;

	public:
		inline static void Print( const r2::Radian& radian )
		{
			std::cout
				<< "\t"

				<< "Radian" "   "

				<< radian

				<< "\n"
			;
		}
	};
}