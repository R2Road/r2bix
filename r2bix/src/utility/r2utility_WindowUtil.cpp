#include "pch.h"
#include "r2utility_WindowUtil.h"

#include <Windows.h>

namespace r2utility
{
	void MoveWindow( const int x, const int y )
	{
		//
		// # MoveWindow( hWnd, 0, 0... ); �����δ� Window �� �������� 0, 0 ��ǥ�� ��ġ���� �ʴ´�.
		// # �Ʒ��� �ڵ带 �̿��ؼ� Ÿ��Ʋ �ٿ� ���� �������� ���� �ؾ߸� �� �ڵ�� 0, 0 ��ġ�� ��������.
		//		LONG lStyle = GetWindowLong( GetConsoleWindow(), GWL_STYLE );
		//		lStyle &= ~( WS_CAPTION | WS_THICKFRAME );
		//		SetWindowLong( GetConsoleWindow(), GWL_STYLE, lStyle );
		//
		// # �� ��ǥ�� Ÿ��Ʋ �ٴ� ���� ������ Window �� 0, 0 �� �ڸ��ϴ� ���̴�.
		// # ���� Frame ũ�⸦ ����ؼ� ������ 0, 0 ��ġ�� ���̰� �ϰ��� �Ѵ�.
		//
		int offset_x = 0;
		offset_x -= GetSystemMetrics( SM_CXBORDER );
		offset_x -= GetSystemMetrics( SM_CXFRAME );
		offset_x -= GetSystemMetrics( SM_CXFIXEDFRAME );

		HWND hWnd = GetConsoleWindow();
		RECT rectClient;
		GetClientRect( hWnd, &rectClient );
		MoveWindow( hWnd, x + offset_x, y, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE );
	}
}