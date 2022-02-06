#pragma once

#include <vector>

namespace r2
{
	class KeyboardInputCollector
	{
	public:
		using KeyCodeTypeT = uint8_t;

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