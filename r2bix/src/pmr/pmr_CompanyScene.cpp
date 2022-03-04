#include "pch.h"
#include "pmr_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"
#include "node/r2node_LabelNode.h"

namespace pmr
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		{
			auto node = r2node::LabelNode::Create( mDirector );
			node->SetRect( 0, 0, 30, 1 );
			node->SetString( CompanyScene::GetTitle() );
			AddChild( std::move( node ) );
		}

		return true;
	}
	void CompanyScene::Update()
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
		}
	}
}