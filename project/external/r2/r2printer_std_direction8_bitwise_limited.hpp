#pragma once

#include <iomanip>
#include <ostream>

#include "r2_none_copyable.hpp"
#include "r2_direction8_bitwise_limited.hpp"

namespace r2printer
{
	class STD_Direction8BitwiseLimited : private r2::NoneCopyable
	{
	private:
		STD_Direction8BitwiseLimited() = delete;

	public:
		inline static void Print( const r2::Direction8BitwiseLimited& v )
		{
			std::cout
				<< "\t" "Direction8BitwiseLimited"

				<< "      "
				   "state  : "	<< std::setw( 3 ) << static_cast<int>( v.GetState() )

				<< "      "
				   "enable : "	<< std::setw( 3 ) << static_cast<int>( v.GetEnableStateFlags() )

				<< "          "
				   "x : "		<< std::setw( 2 ) << v.GetX()
				<< "      "
				   "y : "		<< std::setw( 2 ) << v.GetY()

				<< "\n"
				
				<< std::setw( 0 );
		}
	};
}

inline std::ostream& operator<<( std::ostream& o, const r2::Direction8BitwiseLimited& v )
{
	return o
				<< std::setw( 3 ) << static_cast<int>( v.GetState() )
		<< "  " << std::setw( 3 ) << static_cast<int>( v.GetEnableStateFlags() )
		<< "      "
				<< std::setw( 2 ) << v.GetX()
		<< "  " << std::setw( 2 ) << v.GetY()

		<< std::setw( 0 );
}
inline std::ostream& operator<<( std::ostream& o, const r2::Direction8BitwiseLimited::eState& v )
{
	return o << static_cast<int>( v );
}
