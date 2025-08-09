#pragma once

#include <ostream>

#include "r2_NoneCopyable.h"
#include "r2_Range.h"

namespace r2helper
{
	class STDPrinter4Range : private r2::NoneCopyable
	{
	private:
		STDPrinter4Range() = delete;

	public:
		template<typename T>
		inline static void PrintStartAndDistance( const r2::Range<T>& v )
		{
			std::cout
				<< "\t" "Range"

				<< "      "
				   "start : " << v.GetStart()
				<< "      "
				   "distance : " << v.GetDistance()

				<< "\n";
		}

		template<>
		inline static void PrintStartAndDistance( const r2::Range<char>& v )
		{
			std::cout
				<< "\t" "Range"

				<< "      "
				   "start : " << static_cast<int>( v.GetStart() )
				<< "      "
				   "distance : " << static_cast<int>( v.GetDistance() )

				<< "\n";
		}
		template<>
		inline static void PrintStartAndDistance( const r2::Range<unsigned char>& v )
		{
			std::cout
				<< "\t" "Range"

				<< "      "
				   "start : " << static_cast<int>( v.GetStart() )
				<< "      "
				   "distance : " << static_cast<int>( v.GetDistance() )

				<< "\n";
		}
	};
}

template<typename T>
inline std::ostream& operator<<( std::ostream& o, const r2::Range<T>& v )
{
	return o << v.GetStart() << "   " << v.GetEnd();
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Range<char>& v )
{
	return o << static_cast<int>( v.GetStart() ) << "   " << static_cast<int>( v.GetEnd() );
}

template<>
inline std::ostream& operator<<( std::ostream& o, const r2::Range<unsigned char>& v )
{
	return o << static_cast<int>( v.GetStart() ) << "   " << static_cast<int>( v.GetEnd() );
}