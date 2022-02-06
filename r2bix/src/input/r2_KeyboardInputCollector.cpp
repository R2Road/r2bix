#include "pch.h"

#include <windows.h>

#include "input/r2_KeyboardInputCollector.h"

namespace r2
{
	KeyboardInputCollector::KeyboardInputCollector() :
		mObservationKeyList( { VK_ESCAPE } )
		, mKeyStatusList( 256, 0 )
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
			key_value = GetAsyncKeyState( k );
			mKeyStatusList[k] = key_value & 0x8000;
		}
	}
}