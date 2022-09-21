#include "psnake_CompanyScene.h"

#include <conio.h>

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2component_LabelSComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2node_LabelSNode.h"

namespace psnake
{
	CompanyScene::CompanyScene( r2bix::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp CompanyScene::Create( r2bix::Director& director )
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
		if( !r2base::Node::Init() )
		{
			return false;
		}

		{
			auto node = AddChild<r2node::LabelSNode>();
			node->GetComponent<r2component::LabelSComponent>()->SetString( CompanyScene::GetTitle() );
		}

		return true;
	}
	void CompanyScene::Update( const float delta_time )
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}