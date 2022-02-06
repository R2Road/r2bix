#include "pch.h"
#include "input/r2_input_KeyboardInputCollector.h"

#include <numeric>

#include "r2_input_KeyboardInputListener.h"

namespace r2_input
{
	KeyboardInputCollector::KeyboardInputCollector() : mKeyboardInputListener( nullptr )
	{}

	void KeyboardInputCollector::Collect()
	{
		if( nullptr == mKeyboardInputListener )
		{
			return;
		}

		int key_value = 0;

		for( const auto k : mKeyboardInputListener->mObservationKeyList )
		{
			key_value = GetKeyState( k );
			mKeyboardInputListener->mKeyStatusList[k] = key_value & 0x8000;
		}
	}
}