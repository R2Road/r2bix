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
		// Windows Mouse Position ��������
		//
		POINT mouse_position;
		GetCursorPos( &mouse_position );

		//
		// ���콺 ��ǥ ���� ������ ��ǥ�� ��ȯ
		//
		HWND hwnd = GetConsoleWindow();
		ScreenToClient( hwnd, &mouse_position );

		//
		// �ܼ� ���� : ���� �ܼ��� ���� ���ΰ� ��� ���ڷ� ä�������� ���� ����
		//
		HANDLE hout = GetStdHandle( STD_OUTPUT_HANDLE );
		CONSOLE_SCREEN_BUFFER_INFO bi;
		GetConsoleScreenBufferInfo( hout, &bi );

		//
		// ��Ʈ ����
		//
		CONSOLE_FONT_INFO fi;
		GetCurrentConsoleFont( hout, false, &fi );

		//
		// Ŀ�� ��ǥ ����
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