#include "pch.h"
#include "p2048_GameScene.h"

#include <cassert>
#include <conio.h>

#include "base/r2base_Director.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "node/r2node_SpriteNode.h"

#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	GameScene::GameScene( r2base::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp GameScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) GameScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool GameScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		// Frame
		{
			auto sprite_node = AddChild<r2node::SpriteNode>();
			sprite_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame(
				p2048table::TextureTable::GetInstance().GetTextureFrame( "number_frame_0" )
			);
			sprite_node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.38f
			);
		}

		return true;
	}
	void GameScene::Update( const float delta_time )
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input ) // ESC
			{
				mDirector.RequestAbort();
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}