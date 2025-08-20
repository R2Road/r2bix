#pragma once

#include <iomanip>
#include <ostream>

#include "r2_none_copyable.hpp"
#include "r2_matrix22.hpp"

inline std::ostream& operator<<( std::ostream& o, const r2::Matrix22& m )
{
	static const int w = 15;

	return o
		<< std::left

		<< "\n\t\t"
		<< "11 : " << std::setw( w ) << m._11 << "   "
		<< "12 : " << std::setw( w ) << m._12

		<< "\n\t\t"
		<< "21 : " << std::setw( w ) << m._21 << "   "
		<< "22 : " << std::setw( w ) << m._22 << "   "

		<< std::right
	;
}

namespace r2printer
{
	class STD_Matrix22 : private r2::NoneCopyable
	{
	private:
		STD_Matrix22() = delete;

	public:
		inline static void Print( const r2::Matrix22& m )
		{
			std::cout
				<< std::left

				<< "\t" "Matrix22"

				<< m

				<< "\n"

				<< std::right
			;
		}
	};
}