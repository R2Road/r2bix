#pragma once

#include <iomanip>
#include <ostream>

#include "r2_none_copyable.hpp"
#include "r2_point.hpp"

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Point<T>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "x : " << std::setw( w ) << v.GetX()

		<< "   "

		<< "y : " << std::setw( w ) << v.GetY()

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Point<char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "x : " << std::setw( w ) << static_cast<int>( v.GetX() )

		<< "   "

		<< "y : " << std::setw( w ) << static_cast<int>( v.GetY() )

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Point<unsigned char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "x : " << std::setw( w ) << static_cast<int>( v.GetX() )

		<< "   "

		<< "y : " << std::setw( w ) << static_cast<int>( v.GetY() )

		<< std::right
	;
}

namespace r2printer
{
	class STD_Point : private r2::NoneCopyable
	{
	private:
		STD_Point() = delete;

	public:
		template<typename T>
		inline static void Print( const r2::Point<T>& v )
		{
			std::cout
				<< "\t" "Point"

				<< v

				<< "\n";
		}
	};
}
