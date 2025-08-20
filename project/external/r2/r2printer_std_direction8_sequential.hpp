#pragma once

#include <iomanip>
#include <ostream>

#include "r2_direction8_sequential.hpp"
#include "r2_none_copyable.hpp"

namespace r2printer
{
	class STD_Direction8Sequential : private r2::NoneCopyable
	{
	private:
		STD_Direction8Sequential() = delete;

	public:
		inline static void Print( const r2::Direction8Sequential& v )
		{
			std::cout
				<< "\t"   "Direction8Sequential"

				<< "      "
				"state : " << static_cast<int>( v.GetState() )

				<< "      "
				"x : " << std::setw( 2 ) << static_cast<int>( v.GetX() )
				<< "      "
				"y : " << std::setw( 2 ) << static_cast<int>( v.GetY() )

				<< "\n"

				<< std::setw( 0 );
		}
	};
}

inline std::ostream& operator<<( std::ostream& o, const r2::Direction8Sequential& v )
{
	return o
		<< static_cast<int>( v.GetState() )

		<< "      "
		<< std::setw( 2 ) << static_cast<int>( v.GetX() ) << "  " << std::setw( 2 ) << static_cast<int>( v.GetY() )

		<< std::setw( 0 );
}
inline std::ostream& operator<<( std::ostream& o, const r2::Direction8SequentialState::eState& v )
{
	return o << static_cast<int>( v );
}
