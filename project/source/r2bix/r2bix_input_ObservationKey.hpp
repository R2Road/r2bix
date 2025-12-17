#pragma once

#include "r2bix_input_KeyStatus.hpp"

namespace r2bix_input
{
	struct ObservationKey
	{
		KeyIndexTypeT key_index = 0;
		KeyCodeTypeT key_code = 0;
		KeyStatus key_status;
	};
}