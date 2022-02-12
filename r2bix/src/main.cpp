#include "pch.h"
#include <Windows.h>

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "base/r2base_Director.h"
#include "base/r2base_iNode.h"
#include "scene/DevelopScene.h"

int main()
{
	//
	// Environment : Title
	//
	SetConsoleTitle( TEXT( "r2bix" ) );

	//
	// Environment : Size
	//
	system( "mode con lines=60 cols=120" );

	//
	// Environment : Position
	//
	{
		HWND hWnd = GetConsoleWindow();
		RECT rectClient;
		GetClientRect( hWnd, &rectClient );
		MoveWindow( hWnd, 0, 0, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE );
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
