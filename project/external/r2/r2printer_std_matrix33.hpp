#pragma once

#include <iomanip>
#include <ostream>

#include "r2_none_copyable.hpp"
#include "r2_matrix33.hpp"

inline std::ostream& operator<<( std::ostream& o, const r2::Matrix33& m )
{
	static const int w = 15;

	return o
		<< std::left

		<< "\n\t\t"
		<< "11 : " << std::setw( w ) << m._11 << "   "
		<< "12 : " << std::setw( w ) << m._12 << "   "
		<< "13 : " << std::setw( w ) << m._13

		<< "\n\t\t"
		<< "21 : " << std::setw( w ) << m._21 << "   "
		<< "22 : " << std::setw( w ) << m._22 << "   "
		<< "23 : " << std::setw( w ) << m._23

		<< "\n\t\t"
		<< "31 : " << std::setw( w ) << m._31 << "   "
		<< "32 : " << std::setw( w ) << m._32 << "   "
		<< "33 : " << std::setw( w ) << m._33

		<< std::right
	;
}

namespace r2printer
{
	class STD_Matrix33 : private r2::NoneCopyable
	{
	private:
		STD_Matrix33() = delete;

	public:
		inline static void Print( const r2::Matrix33& m )
		{
			std::cout
				<< std::left

				<< "\t" "Matrix33"

				<< m

				<< "\n"

				<< std::right
			;
		}
	};
}