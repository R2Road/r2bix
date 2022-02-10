#pragma once

#include <vector>

#include "r2_input_Constant.h"

namespace r2_input
{
	class KeyboardInputListener
	{
	public:
		KeyboardInputListener();

		//
		// Getter
		//
		bool IsPressed( const std::size_t key_index ) const
		{
			return mKeyFlags[key_index];
		}

		std::vector<KeyCodeTypeT> mObservationKeyList;
		std::vector<bool> mKeyFlags;
	};
}