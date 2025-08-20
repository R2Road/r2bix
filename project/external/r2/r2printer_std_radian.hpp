#pragma once

#include <iomanip>
#include <iostream>

#include "r2_none_copyable.hpp"
#include "r2_radian.hpp"

inline std::ostream& operator<<( std::ostream& o, const r2::Radian& radian )
{
	static const int w = 10;

	return o
		<< std::left

		<< radian.Get()

		<< std::right;
}

namespace r2printer
{
	class STD_Radian : private r2::NoneCopyable
	{
	private:
		STD_Radian() = delete;

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