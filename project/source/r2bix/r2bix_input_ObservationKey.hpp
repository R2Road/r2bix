#pragma once

#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	struct ObservationKey
	{
		KeyIndexTypeT key_index = 0;
		KeyCodeTypeT key_code = 0;
		eKeyStep key_step = eKeyStep::None;
	};
}