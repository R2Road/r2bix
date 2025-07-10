#pragma once

#include <iomanip>
#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Size.h"

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Size<T>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "w : " << std::setw( w ) << v.GetWidth()

		<< "   "

		<< "h : " << std::setw( w ) << v.GetHeight()

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Size<char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "w : " << std::setw( w ) << static_cast<int>( v.GetWidth() )

		<< "   "

		<< "h : " << std::setw( w ) << static_cast< int >( v.GetHeight() )

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Size<unsigned char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "w : " << std::setw( w ) << static_cast<int>( v.GetWidth() )

		<< "   "

		<< "h : " << std::setw( w ) << static_cast< int >( v.GetHeight() )

		<< std::right
	;
}

namespace r2helper
{
	class STDPrinter4Size : private r2::NoneCopyable
	{
	private:
		STDPrinter4Size() = delete;

	public:
		template<typename T>
		inline static void Print( const r2::Size<T>& v )
		{
			std::cout
				<< "\t" "Size"

				<< v

				<< "\n";
		}
	};
}
