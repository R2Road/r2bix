#pragma once

#include <iomanip>
#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Matrix4.h"

namespace r2helper
{
	class STDPrinter4Matrix4 : private r2::NoneCopyable
	{
	private:
		STDPrinter4Matrix4() = delete;

	public:
		inline static void Print( const r2::Matrix4& v )
		{
			static const int w = 10;

			std::cout
				<< std::left

				<< "\t" "Matrix4"

				<< "\n\t\t"
				<< "11 : " << std::setw( w ) << v._11 << "   "
				<< "12 : " << std::setw( w ) << v._12 << "   "
				<< "13 : " << std::setw( w ) << v._13 << "   "
				<< "14 : " << std::setw( w ) << v._14

				<< "\n\t\t"
				<< "21 : " << std::setw( w ) << v._21 << "   "
				<< "22 : " << std::setw( w ) << v._22 << "   "
				<< "23 : " << std::setw( w ) << v._23 << "   "
				<< "24 : " << std::setw( w ) << v._24

				<< "\n\t\t"
				<< "31 : " << std::setw( w ) << v._31 << "   "
				<< "32 : " << std::setw( w ) << v._32 << "   "
				<< "33 : " << std::setw( w ) << v._33 << "   "
				<< "34 : " << std::setw( w ) << v._34

				<< "\n\t\t"
				<< "41 : " << std::setw( w ) << v._41 << "   "
				<< "42 : " << std::setw( w ) << v._42 << "   "
				<< "43 : " << std::setw( w ) << v._43 << "   "
				<< "44 : " << std::setw( w ) << v._44

				<< "\n"

				<< std::right
			;
		}
	};
}

inline std::ostream& operator<<( std::ostream& o, const r2::Matrix4& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "\t"

		<< std::setw( w ) << v._11 << "   "
		<< std::setw( w ) << v._12 << "   "
		<< std::setw( w ) << v._13 << "   "
		<< std::setw( w ) << v._14

		<< "\n\t"

		<< "\t"
		<< std::setw( w ) << v._21 << "   "
		<< std::setw( w ) << v._22 << "   "
		<< std::setw( w ) << v._23 << "   "
		<< std::setw( w ) << v._24

		<< "\n\t"

		<< "\t"
		<< std::setw( w ) << v._31 << "   "
		<< std::setw( w ) << v._32 << "   "
		<< std::setw( w ) << v._33 << "   "
		<< std::setw( w ) << v._34

		<< "\n\t"

		<< "\t"
		<< std::setw( w ) << v._41 << "   "
		<< std::setw( w ) << v._42 << "   "
		<< std::setw( w ) << v._43 << "   "
		<< std::setw( w ) << v._44

		<< std::right
	;
}