#pragma once

#include <iostream>

#include "r2_none_copyable.hpp"
#include "r2_rect.hpp"

#include "r2printer_std_point.hpp"
#include "r2printer_std_size.hpp"

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Rect<T>& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "     "

		<< "min  "
		<< "x : " << std::setw( w ) << v.GetMinX() << "   "
		<< "y : " << std::setw( w ) << v.GetMinY() << "   "
		<< "max  "
		<< "x : " << std::setw( w ) << v.GetMaxX() << "   "
		<< "y : " << std::setw( w ) << v.GetMaxY() << "   "
		<< "size  "
		<< "w : " << std::setw( w ) << v.GetSize().GetWidth() << "   "
		<< "h : " << std::setw( w ) << v.GetSize().GetHeight()

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Rect<char>& v )
{
	static const int w = 10;

	return o
		<< std::left

		<< "     "

		<< "min  "
		<< "x : " << std::setw( w ) << static_cast<int>( v.GetMinX() ) << "   "
		<< "y : " << std::setw( w ) << static_cast<int>( v.GetMinY() ) << "   "
		<< "max  "
		<< "x : " << std::setw( w ) << static_cast<int>( v.GetMaxX() ) << "   "
		<< "y : " << std::setw( w ) << static_cast<int>( v.GetMaxY() ) << "   "
		<< "size  "
		<< "w : " << std::setw( w ) << static_cast<int>( v.GetSize().GetWidth() ) << "   "
		<< "h : " << std::setw( w ) << static_cast<int>( v.GetSize().GetHeight() )

		<< std::right
	;
}

namespace r2printer
{
	class STD_Rect : private r2::NoneCopyable
	{
	private:
		STD_Rect() = delete;

	public:
		template<typename T>
		inline static void Print( const r2::Rect<T>& v )
		{
			std::cout
				<< "   " "Rect"

				<< v

				<< "\n";
		}
	};
}