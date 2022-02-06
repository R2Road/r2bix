#pragma once

#include <vector>

namespace r2
{
	class KeyboardInputCollector
	{
	public:
		KeyboardInputCollector();

		//
		// Getter
		//
		bool IsPressed( const int key_code ) const;

		void Collect();

	private:
		std::vector<int> mObservationKeyList;
		std::vector<int> mKeyStatusList;
	};
}