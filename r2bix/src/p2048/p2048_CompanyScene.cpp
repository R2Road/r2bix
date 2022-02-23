#include "pch.h"
#include "p2048_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"

#include "scene/DevelopScene.h"

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2game::Scene( director )
	{}

	r2base::NodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		return ret;
	}

	bool CompanyScene::Do()
	{
		std::cout << "# " << "2048 Game Scene" << " #" << r2::linefeed;

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}

		system( "cls" );

		return true;
	}
}