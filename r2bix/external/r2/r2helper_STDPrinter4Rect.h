#pragma once

#include <iostream>

#include "r2_NoneCopyable.h"
#include "r2_Rect.h"

#include "r2helper_STDPrinter4Point.h"
#include "r2helper_STDPrinter4Size.h"

namespace r2helper
{
	class STDPrinter4Rect : private r2::NoneCopyable
	{
	private:
		STDPrinter4Rect() = delete;

	public:
		template<typename T>
		inline static void PrintMinMax( const r2::Rect<T>& v )
		{
			std::cout
				<< "\t" "Rect"

				<< "      "
				   "min : " << v.GetMinX() << "  " << v.GetMinY()
				<< "      "
				   "max : " << v.GetMaxX() << "  " << v.GetMaxY()

				<< "\n";
		}

		template<>
		inline static void PrintMinMax( const r2::Rect<char>& v )
		{
			std::cout
				<< "\t" "Rect"

				<< "      "
				   "min : " << static_cast<int>( v.GetMinX() ) << "  " << static_cast<int>( v.GetMinY() )
				<< "      "
				   "max : " << static_cast<int>( v.GetMaxX() ) << "  " << static_cast<int>( v.GetMaxY() )

				<< "\n";
		}
	};
}

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Rect<T>& v )
{
	return o
		<< v.GetOrigin() << "     " << v.GetSize()
		<< "     ||     "
		<< (long long)v.GetMinX() << "  " << (long long)v.GetMinY() << "     " << (long long)v.GetMaxX() << "  " << (long long)v.GetMaxY()
	;
}