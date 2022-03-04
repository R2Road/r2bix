#include "pch.h"

#include <conio.h>

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "base/r2base_Director.h"
#include "test/scene/DevelopScene.h"
#include "utility/r2utility_WindowUtil.h"

#include "test/r2test_Director.h"
#include "test_r2bix/TestRootMenu.h"

int main()
{
	//
	// Environment : Title
	//
	r2utility::ChangeWindowTitle( L"r2bix" );

	//
	// Environment : Size
	//
	r2utility::ResizeWindow( 960, 960 );

	//
	// Environment : Position
	//
	r2utility::MoveWindow( 0, 0 );

	bool bRun = true;
	do
	{
		system( "cls" );

		std::cout << "# Develop #" << r2::linefeed;

		std::cout << r2::split;

		std::cout << "[ESC] " "Exit" << r2::linefeed2;

		std::cout << "[1] " "Test" << r2::linefeed;
		std::cout << "[2] " "Game" << r2::linefeed;

		const auto input = _getch();
		switch( input )
		{
		case '1':
		{
			//
			// Setup
			//
			r2base::Director director;
			director.Setup( DevelopScene::Create( director ) );

			//
			// Process
			//
			director.Update();
		}
		break;

		case '2':
		{
			//
			// Setup
			//
			r2test::Director director;
			director.Setup( TestRootMenu::Create( director ) );

			//
			// Process
			//
			director.Update();
		}
		break;

		case 27:
			bRun = false;
			break;
		}

	} while( bRun );

	return 0;
}
