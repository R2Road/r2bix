#include "pch.h"
#include "p2048_EntryScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "p2048_CompanyScene.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	EntryScene::EntryScene( r2base::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp EntryScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) EntryScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}
	void EntryScene::Update()
	{
		//
		// Load Resources
		//
		{
			p2048table::TextureTable::GetInstance().Load();
		}

		//
		// Move 2 Company Scene
		//
		mDirector.Setup( p2048::CompanyScene::Create( mDirector ) );
	}
}