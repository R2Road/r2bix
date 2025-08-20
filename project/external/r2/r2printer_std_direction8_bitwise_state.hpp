#pragma once

#include <ostream>

#include "r2_direction8_bitwise_state.hpp"

namespace r2helper
{
}

inline std::ostream& operator<<( std::ostream& o, const r2::Direction8BitwiseState::eState& v )
{
	return o << static_cast<int>( v );
}
