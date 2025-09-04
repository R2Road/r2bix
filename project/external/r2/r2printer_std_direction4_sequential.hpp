#pragma once

#include <iomanip>
#include <ostream>

#include "r2_direction4_sequential.hpp"
#include "r2_none_copyable.hpp"

inline std::ostream& operator<<( std::ostream& o, const r2::Direction4Sequential& v )
{
	static const int w = 5;

	return o
		<< std::left

		<< "     "

		<< "state : " << std::setw( w ) << static_cast<int>( v.GetState() )

		<< "   "

		<< "x : " << std::setw( w ) << static_cast<int>( v.GetX() )

		<< "   "

		<< "y : " << std::setw( w ) << static_cast<int>( v.GetY() )

		<< std::right
	;
}

inline std::ostream& operator<<( std::ostream& o, const r2::Direction4SequentialState::eState& v )
{
	return o << static_cast< int >( v );
}

namespace r2printer
{
	class STD_Direction4Sequential : private r2::NoneCopyable
	{
	private:
		STD_Direction4Sequential() = delete;

	public:
		inline static void Print( const r2::Direction4Sequential& v )
		{
			std::cout
				<< "\t"   "Direction4Sequential"

				<< v

				<< "\n";
		}
	};
}

