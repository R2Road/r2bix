#include "p_mini_adv_GameScene.h"

#include <conio.h>

#include "r2bix/r2base_Director.h"
#include "r2bix/r2component_LabelComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2node_LabelNode.h"

namespace p_mini_adv
{
	GameScene::GameScene( r2base::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp GameScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) GameScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool GameScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		{
			auto node = AddChild<r2node::LabelNode>();
			node->GetComponent<r2component::LabelComponent>()->SetString( GameScene::GetTitle() );

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

		r2node::SceneNode::Update( delta_time );
	}
}