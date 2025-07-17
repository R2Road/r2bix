#pragma once

#include <iomanip>
#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Matrix4.h"

inline std::ostream& operator<<( std::ostream& o, const r2::Matrix4& m )
{
	static const int w = 15;

	return o
		<< std::left

		<< "\n\t\t"
		<< "11 : " << std::setw( w ) << m._11 << "   "
		<< "12 : " << std::setw( w ) << m._12 << "   "
		<< "13 : " << std::setw( w ) << m._13 << "   "
		<< "14 : " << std::setw( w ) << m._14

		<< "\n\t\t"
		<< "21 : " << std::setw( w ) << m._21 << "   "
		<< "22 : " << std::setw( w ) << m._22 << "   "
		<< "23 : " << std::setw( w ) << m._23 << "   "
		<< "24 : " << std::setw( w ) << m._24

		<< "\n\t\t"
		<< "31 : " << std::setw( w ) << m._31 << "   "
		<< "32 : " << std::setw( w ) << m._32 << "   "
		<< "33 : " << std::setw( w ) << m._33 << "   "
		<< "34 : " << std::setw( w ) << m._34

		<< "\n\t\t"
		<< "41 : " << std::setw( w ) << m._41 << "   "
		<< "42 : " << std::setw( w ) << m._42 << "   "
		<< "43 : " << std::setw( w ) << m._43 << "   "
		<< "44 : " << std::setw( w ) << m._44

		<< "\n"

		<< std::right
	;
}

namespace r2helper
{
	class STDPrinter4Matrix4 : private r2::NoneCopyable
	{
	private:
		STDPrinter4Matrix4() = delete;

	public:
		inline static void Print( const r2::Matrix4& m )
		{
			std::cout
				<< std::left

				<< "\t" "Matrix4"

				<< m

				<< "\n"

				<< std::right
			;
		}
	};
}