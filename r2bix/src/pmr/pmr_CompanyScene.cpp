#include "pch.h"
#include "pmr_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"

#include "scene/DevelopScene.h"

namespace pmr
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2game::Scene( director )
	{}

	r2base::NodeUp CompanyScene::Create( r2base::Director& director )
	{
		std::unique_ptr<CompanyScene> ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void CompanyScene::Update()
	{
		std::cout << "# " << "Mini Rogue Game Scene" << " #" << r2::linefeed;

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}

		system( "cls" );
	}
}