#include "r2bix_input_Constant.h"

#include <Windows.h>

namespace r2bix_input
{
	int GetKeyState( const KeyCodeTypeT key_code )
	{
		return GetAsyncKeyState( key_code );
	}

	CursorPoint GetCursorPoint()
	{
		//
		// Windows Mouse Position 가져오기
		//
		POINT mouse_position;
		GetCursorPos( &mouse_position );

		//
		// 마우스 좌표 현재 윈도우 좌표로 변환
		//
		HWND hwnd = GetConsoleWindow();
		ScreenToClient( hwnd, &mouse_position );

		//
		// 콘솔 정보 : 현재 콘솔의 가로 세로가 몇개의 문자로 채워지는지 등의 정보
		//
		HANDLE hout = GetStdHandle( STD_OUTPUT_HANDLE );
		CONSOLE_SCREEN_BUFFER_INFO bi;
		GetConsoleScreenBufferInfo( hout, &bi );

		//
		// 폰트 정보
		//
		CONSOLE_FONT_INFO fi;
		GetCurrentConsoleFont( hout, false, &fi );

		//
		// 커서 좌표 생성
		//
		CursorPoint ret{
				mouse_position.x / fi.dwFontSize.X
			,	mouse_position.y / fi.dwFontSize.Y
		};

		return ret;
	}

	bool IsMouseKeyReversed()
	{
		return ( 0 != GetSystemMetrics( SM_SWAPBUTTON ) );
	}

	bool HasWindowFocus()
	{
		return GetConsoleWindow() == GetForegroundWindow();
	}
}