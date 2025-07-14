#pragma once

#include <iomanip>
#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Vector3.h"

inline std::ostream& operator<<( std::ostream& o, const r2::Vector3& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "\t"

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
	class STDPrinter4Vector3 : private r2::NoneCopyable
	{
	private:
		STDPrinter4Vector3() = delete;

	public:
		inline static void Print( const r2::Vector3& v )
		{
			static const int w = 10;

			std::cout
				<< std::left

				<< "\t" "Vector3"

				<< v

				<< "\n"

				<< std::right;
		}
	};
}