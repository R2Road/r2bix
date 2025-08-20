#pragma once

#include <iomanip>
#include <ostream>

#include "r2_none_copyable.hpp"
#include "r2_range.hpp"

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Range<T>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "start : " << std::setw( w ) << v.GetStart()

		<< "   "

		<< "end : " << std::setw( w ) << v.GetEnd()

		<< "   "

		<< "distance : " << std::setw( w ) << v.GetDistance()
		

		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Range<char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "start : " << std::setw( w ) << static_cast<int>( v.GetStart() )

		<< "   "

		<< "end : " << std::setw( w ) << static_cast<int>( v.GetEnd() )

		<< "   "

		<< "distance : " << std::setw( w ) << static_cast<int>( v.GetDistance() )


		<< std::right
	;
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Range<unsigned char>& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "\t"

		<< "start : " << std::setw( w ) << static_cast<int>( v.GetStart() )

		<< "   "

		<< "end : " << std::setw( w ) << static_cast<int>( v.GetEnd() )

		<< "   "

		<< "distance : " << std::setw( w ) << static_cast<int>( v.GetDistance() )


		<< std::right
	;
}

namespace r2printer
{
	class STD_Range : private r2::NoneCopyable
	{
	private:
		STD_Range() = delete;

	public:
		template<typename T>
		inline static void PrintStartAndDistance( const r2::Range<T>& v )
		{
			std::cout
				<< "\t" "Range"

				<< v

				<< "\n";
		}
	};
}