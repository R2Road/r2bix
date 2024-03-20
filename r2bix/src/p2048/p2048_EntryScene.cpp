#include "p2048_EntryScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "r2bix_Director.h"
#include "p2048_CompanyScene.h"
#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	EntryScene::EntryScene( r2bix::Director& director ) : r2bix_node::Node( director )
	{}

	r2bix_node::NodeUp EntryScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( new ( std::nothrow ) EntryScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}
	void EntryScene::Update( const float delta_time )
	{
		//
		// Load Resources
		//
		{
			p2048table::TextureTable::GetInstance().Load();
			p2048table::TextureFrameAnimationTable::GetInstance().Load();
		}

		//
		// Move 2 Company Scene
		//
		mDirector.Setup( p2048::CompanyScene::Create( mDirector ) );

		r2bix_node::Node::Update( delta_time );
	}
}