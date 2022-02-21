#include "pch.h"
#include "pmr_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"

#include "scene/DevelopScene.h"
#include "game/r2game_Scene.h"

namespace r2game
{
	RootScene::RootScene( r2base::Director& director ) : GameScene( director )
	{}

	r2base::NodeUp RootScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) RootScene( director ) );
		return ret;
	}

	bool RootScene::Do()
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
}