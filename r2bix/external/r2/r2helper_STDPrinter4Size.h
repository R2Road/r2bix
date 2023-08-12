#pragma once

#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Size.h"

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

				<< "      "
				   "w : " << v.GetWidth()
				<< "      "
				   "h : " << v.GetHeight()

				<< "\n";
		}

		template<>
		inline static void Print( const r2::Size<char>& v )
		{
			std::cout
				<< "\t" "Size"

				<< "      "
				   "w : " << static_cast<int>( v.GetWidth() )
				<< "      "
				   "h : " << static_cast<int>( v.GetHeight() )

				<< "\n";
		}
		template<>
		inline static void Print( const r2::Size<unsigned char>& v )
		{
			std::cout
				<< "\t" "Size"

				<< "      "
				   "w : " << static_cast<int>( v.GetWidth() )
				<< "      "
				   "h : " << static_cast<int>( v.GetHeight() )

				<< "\n";
		}
	};
}

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Size<T>& v )
{
	return o << v.GetWidth() << "  " << v.GetHeight();
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Size<char>& v )
{
	return o << static_cast<int>( v.GetWidth() ) << "  " << static_cast<int>( v.GetHeight() );
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Size<unsigned char>& v )
{
	return o << static_cast<int>( v.GetWidth() ) << "  " << static_cast<int>( v.GetHeight() );
}