#include "pch.h"
#include "input/r2_input_KeyboardInputCollector.h"

#include <numeric>

namespace r2_input
{
	KeyboardInputCollector::KeyboardInputCollector() :
		mObservationKeyList( { 27 } )
		, mKeyStatusList( std::numeric_limits<KeyCodeTypeT>::max(), 0 )
	{}

	//
	// Getter
	//
	bool KeyboardInputCollector::IsPressed( const KeyCodeTypeT key_code ) const
	{
		return mKeyStatusList[key_code];
	}

	void KeyboardInputCollector::Collect()
	{
		int key_value = 0;

		for( const auto k : mObservationKeyList )
		{
			key_value = GetKeyState( k );
			mKeyStatusList[k] = key_value & 0x8000;
		}
	}
}