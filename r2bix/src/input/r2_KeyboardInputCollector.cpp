#include "pch.h"

#include <windows.h>

#include "input/r2_KeyboardInputCollector.h"

namespace r2
{
	KeyboardInputCollector::KeyboardInputCollector() : mbPressed( false )
	{}

	//
	// Getter
	//
	bool KeyboardInputCollector::IsPressed( const int /*key_code*/ ) const
	{
		return mbPressed;
	}

	void KeyboardInputCollector::Collect()
	{
		int key_value = 0;

		key_value = GetAsyncKeyState( VK_ESCAPE );

		mbPressed = key_value & 0x8000;
	}
}