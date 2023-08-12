#pragma once

#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Point.h"

namespace r2helper
{
	class STDPrinter4Point : private r2::NoneCopyable
	{
	private:
		STDPrinter4Point() = delete;

	public:
		template<typename T>
		inline static void Print( const r2::Point<T>& v )
		{
			std::cout
				<< "\t" "Point"

				<< "      "
				   "x : " << v.GetX()
				<< "      "
				   "y : " << v.GetY()

				<< "\n";
		}

		template<>
		inline static void Print( const r2::Point<char>& v )
		{
			std::cout
				<< "\t" "Point"

				<< "      "
				   "x : " << static_cast<int>( v.GetX() )
				<< "      "
				   "y : " << static_cast<int>( v.GetY() )

				<< "\n";
		}
		template<>
		inline static void Print( const r2::Point<unsigned char>& v )
		{
			std::cout
				<< "\t" "Point"

				<< "      "
				   "x : " << static_cast<int>( v.GetX() )
				<< "      "
				   "y : " << static_cast<int>( v.GetY() )

				<< "\n";
		}
	};
}

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Point<T>& v )
{
	return o << v.GetX() << "  " << v.GetY();
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Point<char>& v )
{
	return o << static_cast<int>( v.GetX() ) << "  " << static_cast<int>( v.GetY() );
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Point<unsigned char>& v )
{
	return o << static_cast<int>( v.GetX() ) << "  " << static_cast<int>( v.GetY() );
}