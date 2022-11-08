#include "psnake_CompanyScene.h"

#include <conio.h>

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_component_LabelSComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_LabelSNode.h"

namespace psnake
{
	CompanyScene::CompanyScene( r2bix::Director& director ) : r2bix_node::SceneNode( director )
	{}

	r2bix_node::SceneNodeUp CompanyScene::Create( r2bix::Director& director )
	{
		r2bix_node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		if( !r2bix_node::Node::Init() )
		{
			return false;
		}

		{
			auto node = AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2bix_component::LabelSComponent>()->SetString( CompanyScene::GetTitle() );
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

		r2bix_node::SceneNode::Update( delta_time );
	}
}