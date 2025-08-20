#pragma once

#include <iomanip>
#include <iostream>

#include "r2_none_copyable.hpp"
#include "r2_degree.hpp"

inline std::ostream& operator<<( std::ostream& o, const r2::Degree& degree )
{
	static const int w = 10;

	return o
		<< std::left

		<< degree.Get()

		<< std::right;
}

namespace r2printer
{
	class STD_Degree : private r2::NoneCopyable
	{
	private:
		STD_Degree() = delete;

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