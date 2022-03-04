#include "pch.h"
#include "TestScene.h"

#include <cctype> // std::toupper
#include <conio.h>

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"
#include "test/r2test_iTest.h"

namespace
{
	const char KeyCode4LineFeed = 64; // @
	const char KeyCode4Split = 42; // *
}

TestScene::TestScene( r2base::Director& director, const char* title_string, const char* description_string ) : r2node::SceneNode( director )
	, mTitleString( title_string )
	, mDescriptionString( description_string )
	, mTests()
{}

void TestScene::ShowInformation() const
{
	showTitle();
	showDescription();
	showMenu();
}

void TestScene::Update()
{
	mDirector.ClearScreen();

	ShowInformation();
	auto input = _getch();

	mDirector.ClearScreen();

	switch( RunTest( input ) )
	{
	//case r2test::eTestEndAction::None: break;

	case r2test::eTestEndAction::Pause:
		std::cout << r2::linefeed;
		system( "pause" );
		break;

	case r2test::eTestEndAction::Exit:
		mDirector.RequestAbort();
		break;
	}
}

void TestScene::showTitle() const
{
	std::cout << "# " << mTitleString << " #" << r2::linefeed;
	std::cout << r2::split;
}
void TestScene::showDescription() const
{
	if( !mDescriptionString.empty() )
	{
		std::cout << "+ Message" << r2::linefeed2;
			
		std::cout << mDescriptionString << r2::linefeed;

		std::cout << r2::split;
	}
}
void TestScene::showMenu() const
{
	std::cout << "+ Menu" << r2::linefeed2;

	for( const auto t : mTests )
	{
		//
		// Key
		//
		if( KeyCode4Split == t.KeyCode ) // *
		{
			std::cout << r2::split;
			continue;
		}
		if( KeyCode4LineFeed == t.KeyCode ) // @
		{
			std::cout << r2::linefeed;
			continue;
		}

		std::cout << "[";

		if( 27 == t.KeyCode ) // ESC
		{
			std::cout << "ESC";
		}
		else if( 32 == t.KeyCode ) // SPACE_BAR
		{
			std::cout << "SPACE";
		}
		else
		{
			std::cout << static_cast<char>( std::toupper( t.KeyCode ) );
		}

		std::cout << "] ";
			
		//
		// Name
		//
		std::cout << t.NameFunction() << r2::linefeed;
	}

	std::cout << r2::split << "Select Menu";
}

r2test::eTestEndAction TestScene::RunTest( const int key_code )
{
	for( const auto t : mTests )
	{
		if( key_code == t.KeyCode )
		{
			return t.TestFunction( mDirector );
		}
	}

	return r2test::eTestEndAction::Pause;
}

void TestScene::AddChild( const char key_code, r2test::iTest_Deprecated& test_obj )
{
	mTests.emplace_back( key_code, test_obj.GetTitleFunction(), test_obj.GetDoFunction() );
}
void TestScene::AddChild( const char key_code, const std::function<const char*( )> func_title, const std::function<const r2test::eTestEndAction( r2base::Director& )> func_test )
{
	mTests.emplace_back( key_code, func_title, func_test );
}
void TestScene::AddLineFeed()
{
	static const std::function<const char*()> func_title = []()->const char* { return ""; };
	static const std::function<const r2test::eTestEndAction( r2base::Director& )> func_test = []( r2base::Director& )->const r2test::eTestEndAction { return r2test::eTestEndAction::Pause; };

	mTests.push_back( { KeyCode4LineFeed, func_title, func_test } );
}
void TestScene::AddSplit()
{
	static const std::function<const char*( )> func_title = []()->const char* { return ""; };
	static const std::function<const r2test::eTestEndAction( r2base::Director& )> func_test = []( r2base::Director& )->const r2test::eTestEndAction { return r2test::eTestEndAction::Pause; };

	mTests.push_back( { KeyCode4Split, func_title, func_test } );
}