#include "pch.h"
#include "GameScene.h"

#include <conio.h>

#include "base/r2base_Director.h"
#include "scene/DevelopScene.h"

GameScene::GameScene( r2base::Director& director ) : iNode( director )
{}

bool GameScene::Do()
{
	std::cout << "# " << "Empty Game Scene" << " #" << r2::linefeed;
	
	auto input = _getch();
	if( 27 == input )
	{
		mDirector.Setup( DevelopScene::Create( mDirector ) );
	}

	system( "cls" );

	return true;
}