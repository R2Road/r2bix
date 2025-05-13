#pragma once

#include <ostream>

#include "r2_Direction8BitwiseState.h"

namespace r2helper
{
}

inline std::ostream& operator<<( std::ostream& o, const r2::Direction8BitwiseState::eState& v )
{
	return o << static_cast<int>( v );
}
