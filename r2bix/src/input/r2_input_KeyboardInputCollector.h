#pragma once

#include <vector>

#include "r2_input_Constant.h"

namespace r2_input
{
	class KeyboardInputCollector
	{
	public:
		KeyboardInputCollector();

		//
		// Getter
		//
		bool IsPressed( const KeyCodeTypeT key_code ) const;

		void Collect();

	private:
		std::vector<int> mObservationKeyList;
		std::vector<int> mKeyStatusList;
	};
}