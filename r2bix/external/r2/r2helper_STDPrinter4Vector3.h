#pragma once

#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Vector3.h"

namespace r2helper
{
	class STDPrinter4Vector3 : private r2::NoneCopyable
	{
	private:
		STDPrinter4Vector3() = delete;

	public:
		inline static void Print( const r2::Vector3& v )
		{
			std::cout
				<< "\t" "Vector3"

				<< "      "
				   "x : " << v.x
				<< "      "
				   "y : " << v.y
				<< "      "
				   "z : " << v.z

				<< "\n";
		}
	};
}

inline std::ostream& operator<<( std::ostream& o, const r2::Vector3& v )
{
	return o << v.x << "   " << v.y << "   " << v.z;
}