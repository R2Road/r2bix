#include "pch.h"
#include <Windows.h>

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "base/r2base_Director.h"
#include "base/r2base_iNode.h"
#include "scene/DevelopScene.h"
#include "utility/r2utility_WindowUtil.h"

int main()
{
	//
	// Environment : Title
	//
	SetConsoleTitle( TEXT( "r2bix" ) );

	//
	// Environment : Size
	//
	{
		HWND hWnd = GetConsoleWindow();
		RECT window_rect;
		GetClientRect( hWnd, &window_rect );
		MoveWindow( hWnd, window_rect.left, window_rect.top, 960, 960, TRUE );
	}

	//
	// Environment : Position
	//
	{
		r2utility::MoveWindow( 0, 0 );
	}

	//
	// Setup
	//
	r2base::Director director;
	director.Setup( DevelopScene::Create( director ) );

	//
	// Process
	//
	director.Update();

	return 0;
}
