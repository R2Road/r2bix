#include "pch.h"
#include "p2048_TitleScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "action/r2action_BlinkAction.h"
#include "action/r2action_RepeatAction.h"
#include "base/r2base_Director.h"
#include "component/r2component_ActionProcessComponent.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_SpriteNode.h"

#include "p2048_GameScene.h"
#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	TitleScene::TitleScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mLabelNode( nullptr )
		, mSpriteNode( nullptr )
	{}

	r2node::SceneNodeUp TitleScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) TitleScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool TitleScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		//
		// Logo
		//
		{
			// Frame
			{
				mSpriteNode = AddChild<r2node::SpriteNode>();

				auto frame = p2048table::TextureTable::GetInstance().GetTextureFrame( "title_frame" );

				mSpriteNode->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( frame );

				mSpriteNode->mTransformComponent->SetPosition(
					mDirector.GetScreenBufferSize().GetWidth() * 0.5f
					, mDirector.GetScreenBufferSize().GetHeight() * 0.38f
				);
			}

			// Number 2
			{
				auto number_node = mSpriteNode->AddChild<r2node::SpriteNode>();
				number_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "title_2" ) );
				number_node->mTransformComponent->SetPosition( -26, 0 );
			}
			// Number 0
			{
				auto number_node = mSpriteNode->AddChild<r2node::SpriteNode>();
				number_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "title_0" ) );
				number_node->mTransformComponent->SetPosition( -9, 0 );
			}
			// Number 4
			{
				auto number_node = mSpriteNode->AddChild<r2node::SpriteNode>();
				number_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "title_4" ) );
				number_node->mTransformComponent->SetPosition( 9, 0 );
			}
			// Number 8
			{
				auto number_node = mSpriteNode->AddChild<r2node::SpriteNode>();
				number_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "title_8" ) );
				number_node->mTransformComponent->SetPosition( 26, 0 );
			}
		}

		//
		// Company Name
		//
		{
			mLabelNode = AddChild<r2node::LabelNode>();

			mLabelNode->GetComponent<r2component::LabelComponent>()->SetString( "Press Any Key" );

			mLabelNode->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.65f
			);

			auto action_process_component = mLabelNode->AddComponent<r2component::ActionProcessComponent>();

			auto repeat_action = r2action::RepeatAction::Create();

			auto blink_action = r2action::BlinkAction::Create();
			blink_action->SetTimeLimit4Show( 1.1f );
			blink_action->SetTimeLimit4Hide( 0.5f );

			repeat_action->SetAction( std::move( blink_action ) );

			action_process_component->SetAction( std::move( repeat_action ) );
			action_process_component->StartAction();
		}

		return true;
	}
	void TitleScene::Update( const float delta_time )
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
			else if( 32 == input ) // Space
			{
				mDirector.Setup( p2048::GameScene::Create( mDirector ) );
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}