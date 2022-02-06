#pragma once

#include <vector>

#include "r2_input_Constant.h"

namespace r2
{
	class KeyboardInputCollector
	{
	public:
		KeyboardInputCollector();

		//
		// Getter
		//
		bool IsPressed( const r2_input::KeyCodeTypeT key_code ) const;

		void Collect();

	private:
		std::vector<int> mObservationKeyList;
		std::vector<int> mKeyStatusList;
	};
}