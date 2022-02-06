#pragma once

#include <vector>

#include "r2_input_Constant.h"

namespace r2_input
{
	struct KeyboardInputListener
	{
	public:
		KeyboardInputListener();

		//
		// Getter
		//
		bool IsPressed( const KeyCodeTypeT key_code ) const
		{
			return mKeyStatusList[key_code];
		}

		std::vector<KeyCodeTypeT> mObservationKeyList;
		std::vector<int> mKeyStatusList;
	};
}