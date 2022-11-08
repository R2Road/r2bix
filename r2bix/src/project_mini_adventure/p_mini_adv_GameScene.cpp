#include "p_mini_adv_GameScene.h"

#include <conio.h>

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_component_LabelSComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_LabelSNode.h"

namespace p_mini_adv
{
	GameScene::GameScene( r2bix::Director& director ) : r2bix_node::SceneNode( director )
	{}

	r2bix_node::SceneNodeUp GameScene::Create( r2bix::Director& director )
	{
		r2bix_node::SceneNodeUp ret( new ( std::nothrow ) GameScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool GameScene::Init()
	{
		if( !r2bix_node::Node::Init() )
		{
			return false;
		}

		{
			auto node = AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2bix_component::LabelSComponent>()->SetString( GameScene::GetTitle() );

			node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.5f
			);
		}

		return true;
	}
	void GameScene::Update( const float delta_time )
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