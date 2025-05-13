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
			std::cout
				<< "\t" "Matrix4"

				<< "\n\t\t"
				<< "11 : " << v._11 << "   " << "12 : " << v._12 << "   " << "13 : " << v._13 << "   " << "14 : " << v._14

				<< "\n\t\t"
				<< "21 : " << v._21 << "   " << "22 : " << v._22 << "   " << "23 : " << v._23 << "   " << "24 : " << v._24

				<< "\n\t\t"
				<< "31 : " << v._31 << "   " << "32 : " << v._32 << "   " << "33 : " << v._33 << "   " << "34 : " << v._34

				<< "\n\t\t"
				<< "41 : " << v._41 << "   " << "42 : " << v._42 << "   " << "43 : " << v._43 << "   " << "44 : " << v._44

				<< "\n"
			;
		}
	};
}

inline std::ostream& operator<<( std::ostream& o, const r2::Matrix4& v )
{
	return o
		<< "\t"
		<< v._11 << "   " << v._12 << "   " << v._13 << "   " << v._14

		<< "\n\t"

		<< "\t"
		<< v._21 << "   " << v._22 << "   " << v._23 << "   " << v._24

		<< "\n\t"

		<< "\t"
		<< v._31 << "   " << v._32 << "   " << v._33 << "   " << v._34

		<< "\n\t"

		<< "\t"
		<< v._41 << "   " << v._42 << "   " << v._43 << "   " << v._44
	;
}