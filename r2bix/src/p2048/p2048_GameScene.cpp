#include "pch.h"
#include "p2048_GameScene.h"

#include <cassert>
#include <conio.h>
#include <numeric>

#include "base/r2base_Director.h"
#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_CustomTextureNode.h"
#include "node/r2node_PivotNode.h"

#include "p2048/p2048_NumberNode.h"
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

		//
		// Background
		//
		{
			auto node = AddChild<r2node::CustomTextureNode>();
			node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 31, 21, 'S' );
			node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect();

			node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.5f
			);
		}

		// Number
		{
			auto node = AddChild<p2048::NumberNode>( 1 );
			node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.38f
			);
		}

		//
		// Debug
		//
		{
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() - 1, 0 );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() - 1, mDirector.GetScreenBufferSize().GetHeight() - 1 );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( 0, mDirector.GetScreenBufferSize().GetHeight() - 1 );

			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() * 0.5f, mDirector.GetScreenBufferSize().GetHeight() * 0.5f );
		
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