#include "pch.h"

#include <conio.h>

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "base/r2base_Director.h"
#include "utility/r2utility_WindowUtil.h"
#include "pmr/pmr_CompanyScene.h"
#include "p2048/p2048_CompanyScene.h"

#include "r2cm/r2cm_Director.h"
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

		std::cout << "+ Menu" << r2::linefeed2;

		std::cout << "[ESC] " "Exit" << r2::linefeed2;

		std::cout << "[1] " "Test" << r2::linefeed;
		std::cout << "[2] " "Game : 2048" << r2::linefeed;
		std::cout << "[3] " "Game : Mini Rogue" << r2::linefeed;

		std::cout << r2::split;

		std::cout << "Select Menu";

		const auto input = _getch();
		switch( input )
		{
		case '1':
		{
			//
			// Setup
			//
			r2cm::Director director;
			director.Setup( TestRootMenu::Create( director ) );

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
			r2base::Director director;
			director.Setup( p2048::CompanyScene::Create( director ) );

			//
			// Process
			//
			director.Update();
		}
		break;

		case '3':
		{
			//
			// Setup
			//
			r2base::Director director;
			director.Setup( pmr::CompanyScene::Create( director ) );

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
