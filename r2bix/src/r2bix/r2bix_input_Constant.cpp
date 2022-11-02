#include "r2bix_input_Constant.h"

#include <Windows.h>

namespace r2bix_input
{
	int GetKeyState( const KeyCodeTypeT key_code )
	{
		return GetAsyncKeyState( key_code );
	}
	bool HasWindowFocus()
	{
		return GetConsoleWindow() == GetForegroundWindow();
	}
}