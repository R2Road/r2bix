#include "pch.h"
#include "p2048mini_GameScene.h"

#include <numeric>

#include "action/r2action_SequenceAction.h"
#include "action/r2action_DelayAction.h"
#include "action/r2action_MoveByAction.h"
#include "action/r2action_MoveToAction.h"
#include "base/r2base_Director.h"
#include "component/r2component_ActionProcessComponent.h"
#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_CustomTextureNode.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_PivotNode.h"
#include "node/r2node_SpriteNode.h"

#include "p2048mini_GameComponent.h"
#include "p2048mini_StageViewComponent.h"
#include "p2048mini_StageViewNode.h"
#include "p2048minitable_TextureTable.h"

#include "p2048mini_Config.h"

namespace p2048mini
{
	GameScene::GameScene( r2base::Director& director ) : r2node::SceneNode( director )
	{
		
	}

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
		// Table Load
		//
		p2048minitable::TextureTable::GetInstance().Load();

		//
		// Background
		//
		{
			auto node = AddChild<r2node::CustomTextureNode>( std::numeric_limits<int>::min() );
			node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 37, 17, '=' );
			node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
			node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect();

			node->mTransformComponent->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f ) - ( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->GetHeight() * 0.5f )
			);
		}

		//
		// Game Component
		//
		auto game_component = AddComponent<p2048mini::GameComponent>();


		//
		// Title
		//
		{
			auto sprite_node = AddChild<r2node::SpriteNode>();
			sprite_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048minitable::TextureTable::GetInstance().GetTextureFrame( "title_0" ) );
			sprite_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.20f )
			);
		}

		//
		// Stage
		//
		{
			auto stage_view_node = AddChild<p2048mini::StageViewNode>( 1 );
			stage_view_node->SetVisible( false );

			auto stage_view_component = stage_view_node->GetComponent<p2048mini::StageViewComponent>();
			stage_view_component->Setup( &game_component->GetStage() );

			stage_view_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f ) - ( stage_view_component->GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( stage_view_component->GetHeight() * 0.5f )
			);

			//
			//
			//
			game_component->SetStageViewComponent( stage_view_component );
		}

		//
		// Score
		//
		{
			auto label_node = AddChild<r2node::LabelNode>();
			label_node->GetComponent<r2component::LabelComponent>()->SetString( "Score : " );
			label_node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			label_node->GetComponent<r2component::TransformComponent>()->SetPosition( 57, 16 );

			auto score_label_node = AddChild<r2node::LabelNode>( 1 );
			score_label_node->GetComponent<r2component::LabelComponent>()->SetString( "0" );
			score_label_node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			score_label_node->GetComponent<r2component::TransformComponent>()->SetPosition( 72, 16 );

			//
			//
			//
			game_component->SetScoreLabel( score_label_node );
		}

		//
		// Max Number
		//
		{
			auto label_node = AddChild<r2node::LabelNode>();
			label_node->GetComponent<r2component::LabelComponent>()->SetString( "Max : " );
			label_node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			label_node->GetComponent<r2component::TransformComponent>()->SetPosition( 57, 15 );

			auto max_number_label_node = AddChild<r2node::LabelNode>( 1 );
			max_number_label_node->GetComponent<r2component::LabelComponent>()->SetString( "0" );
			max_number_label_node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			max_number_label_node->GetComponent<r2component::TransformComponent>()->SetPosition( 72, 15 );

			//
			//
			//
			game_component->SetMaxNumberLabel( max_number_label_node );
		}

		//
		// Key Info
		//
		{
			auto sprite_node = AddChild<r2node::SpriteNode>();
			sprite_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048minitable::TextureTable::GetInstance().GetTextureFrame( "keyinfo_0" ) );
			sprite_node->GetComponent<r2component::TransformComponent>()->SetPosition( 46, 37 );
		}

		//
		// You Win
		//
		{
			auto you_win_node = AddChild<r2node::SpriteNode>( 2 );
			you_win_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048minitable::TextureTable::GetInstance().GetTextureFrame( "you_win_0" ) );
			you_win_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f )
			);
			you_win_node->SetVisible( false );

			auto action_process_component = you_win_node->AddComponent<r2component::ActionProcessComponent>();
			{
				auto sequence_action = r2action::SequenceAction::Create();

				auto moveto_action = sequence_action->AddAction<r2action::MoveToAction>();
				moveto_action->SetEndPoint( you_win_node->GetComponent<r2component::TransformComponent>()->GetPosition() );
				moveto_action->SetTimeLimit( 0.f );

				auto delay_action = sequence_action->AddAction<r2action::DelayAction>();
				delay_action->SetTimeLimit( 1.f );

				auto moveby_action = sequence_action->AddAction<r2action::MoveByAction>();
				moveby_action->SetMoveAmount( r2::PointInt( 0, 16 ) );
				moveby_action->SetTimeLimit( 1.2f );

				action_process_component->SetAction( std::move( sequence_action ) );
			}

			//
			//
			//
			game_component->SetYouWinNode( you_win_node );
		}

		//
		// Game Over
		//
		{
			auto game_over_node = AddChild<r2node::SpriteNode>( 2 );
			game_over_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048minitable::TextureTable::GetInstance().GetTextureFrame( "game_over_0" ) );
			game_over_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f )
			);
			game_over_node->SetVisible( false );

			auto action_process_component = game_over_node->AddComponent<r2component::ActionProcessComponent>();
			{
				auto sequence_action = r2action::SequenceAction::Create();

				auto moveto_action = sequence_action->AddAction<r2action::MoveToAction>();
				moveto_action->SetEndPoint( game_over_node->GetComponent<r2component::TransformComponent>()->GetPosition() );
				moveto_action->SetTimeLimit( 0.f );

				auto delay_action = sequence_action->AddAction<r2action::DelayAction>();
				delay_action->SetTimeLimit( 1.f );

				auto moveby_action = sequence_action->AddAction<r2action::MoveByAction>();
				moveby_action->SetMoveAmount( r2::PointInt( 0, 16 ) );
				moveby_action->SetTimeLimit( 1.2f );

				action_process_component->SetAction( std::move( sequence_action ) );
			}

			//
			//
			//
			game_component->SetGameOverNode( game_over_node );
		}

		//
		// Debug
		//
		if( p2048mini::Config::GetDebugConfig().bLastStage )
		{
			auto stage_view_node = AddChild<p2048mini::StageViewNode>( 1 );

			auto stage_view_component_4debug = stage_view_node->GetComponent<p2048mini::StageViewComponent>();
			stage_view_component_4debug->Setup( &game_component->GetStage() );

			stage_view_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				0.f
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( stage_view_component_4debug->GetHeight() * 0.5f )
			);

			//
			//
			//
			game_component->SetStageViewComponent4Debug( stage_view_component_4debug );
		}
		if( p2048mini::Config::GetNodeConfig().pivot )
		{
			//
			//
			//
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() - 1, 0 );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() - 1, mDirector.GetScreenBufferSize().GetHeight() - 1 );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( 0, mDirector.GetScreenBufferSize().GetHeight() - 1 );

			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() * 0.5f, mDirector.GetScreenBufferSize().GetHeight() * 0.5f );
		}

		return true;
	}
}