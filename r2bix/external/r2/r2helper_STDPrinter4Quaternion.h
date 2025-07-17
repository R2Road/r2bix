#pragma once

#include <iomanip>
#include <iostream>

#include "r2_NoneCopyable.h"
#include "r2_Quaternion.h"

inline std::ostream& operator<<( std::ostream& o, const r2::Quaternion& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "\t"

		<< "   "
		"w : " << std::setw( w ) << v.w
		<< "   "
		"x : " << std::setw( w ) << v.x
		<< "   "
		"y : " << std::setw( w ) << v.y
		<< "   "
		"z : " << std::setw( w ) << v.z

		<< std::right;
}

namespace r2helper
{
	class STDPrinter4Quaternion : private r2::NoneCopyable
	{
	private:
		STDPrinter4Quaternion() = delete;

	public:
		inline static void Print( const r2::Quaternion& v )
		{
			std::cout
				<< std::left

				<< "\t" "Quaternion"

				<< v

				<< "\n"

				<< std::right;
		}
	};
}