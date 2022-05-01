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

#include "p2048mini_Config.h"
#include "p2048mini_Stage.h"
#include "p2048mini_StageViewComponent.h"
#include "p2048mini_StageViewNode.h"
#include "p2048minitable_TextureTable.h"

#include "r2/r2_Random.h"
#include "utility/r2utility_InputUtil.h"
#include "utility/r2utility_StringBuilder.h"

namespace p2048mini
{
	GameScene::GameScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mStep( eStep::GameReady )
		, mStage( 4u, 4u )
		, mGameProcessor( &mStage )
		, mStageViewComponent( nullptr )
		, mStageViewComponent4Debug( nullptr )

		, mScoreLabel( nullptr )
		, mMaxNumberLabel( nullptr )
		, mGameOverNode( nullptr )

		, mKeyboardInputCollector()
		, mKeyboardInputListener( {
			0x1B		// esc
			, 0x41		// a - left
			, 0x44		// d - right
			, 0x53		// s - down
			, 0x57		// w - up
			, 0x52		// r - reset
		} )
	{
		mKeyboardInputCollector.AddListener( &mKeyboardInputListener );
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
		// Title
		//
		{
			mGameOverNode = AddChild<r2node::SpriteNode>();
			mGameOverNode->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048minitable::TextureTable::GetInstance().GetTextureFrame( "title_0" ) );
			mGameOverNode->GetComponent<r2component::TransformComponent>()->SetPosition(
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

			mStageViewComponent = stage_view_node->GetComponent<p2048mini::StageViewComponent>();
			mStageViewComponent->Setup( &mStage );

			stage_view_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f ) - ( mStageViewComponent->GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( mStageViewComponent->GetHeight() * 0.5f )
			);
		}

		//
		// Score
		//
		{
			auto label_node = AddChild<r2node::LabelNode>();
			label_node->GetComponent<r2component::LabelComponent>()->SetString( "Score : " );
			label_node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			label_node->GetComponent<r2component::TransformComponent>()->SetPosition( 57, 16 );

			mScoreLabel = AddChild<r2node::LabelNode>( 1 );
			mScoreLabel->GetComponent<r2component::LabelComponent>()->SetString( "0" );
			mScoreLabel->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			mScoreLabel->GetComponent<r2component::TransformComponent>()->SetPosition( 72, 16 );
		}

		//
		// Max Number
		//
		{
			auto label_node = AddChild<r2node::LabelNode>();
			label_node->GetComponent<r2component::LabelComponent>()->SetString( "Max : " );
			label_node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			label_node->GetComponent<r2component::TransformComponent>()->SetPosition( 57, 15 );

			mMaxNumberLabel = AddChild<r2node::LabelNode>( 1 );
			mMaxNumberLabel->GetComponent<r2component::LabelComponent>()->SetString( "0" );
			mMaxNumberLabel->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 1.f, 0.f );
			mMaxNumberLabel->GetComponent<r2component::TransformComponent>()->SetPosition( 72, 15 );
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
		// Game Over
		//
		{
			mGameOverNode = AddChild<r2node::SpriteNode>( 2 );
			mGameOverNode->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048minitable::TextureTable::GetInstance().GetTextureFrame( "game_over_0" ) );
			mGameOverNode->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f )
			);
			mGameOverNode->SetVisible( false );

			auto action_process_component = mGameOverNode->AddComponent<r2component::ActionProcessComponent>();
			{
				auto sequence_action = r2action::SequenceAction::Create();

				auto moveto_action = sequence_action->AddAction<r2action::MoveToAction>();
				moveto_action->SetEndPoint( mGameOverNode->GetComponent<r2component::TransformComponent>()->GetPosition() );
				moveto_action->SetTimeLimit( 0.f );

				auto delay_action = sequence_action->AddAction<r2action::DelayAction>();
				delay_action->SetTimeLimit( 1.f );

				auto moveby_action = sequence_action->AddAction<r2action::MoveByAction>();
				moveby_action->SetMoveAmount( r2::PointInt( 0, 16 ) );
				moveby_action->SetTimeLimit( 1.2f );

				action_process_component->SetAction( std::move( sequence_action ) );
			}
		}

		//
		// Debug
		//
		if( p2048mini::Config::GetNodeConfig().pivot )
		{
			//
			// Debug Stage
			//
			{
				auto stage_view_node = AddChild<p2048mini::StageViewNode>( 1 );
				//stage_view_node->SetVisible( false );

				mStageViewComponent4Debug = stage_view_node->GetComponent<p2048mini::StageViewComponent>();
				mStageViewComponent4Debug->Setup( &mStage );

				stage_view_node->GetComponent<r2component::TransformComponent>()->SetPosition(
					0.f
					, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( mStageViewComponent4Debug->GetHeight() * 0.5f )
				);
			}

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
	void GameScene::Update( const float delta_time )
	{
		mKeyboardInputCollector.Collect();
		mKeyboardInputListener.Update();

		switch( mStep )
		{
		case eStep::GameReset:
			mStageViewComponent->GetOwnerNode().SetVisible( false );
			mGameProcessor.Reset();
			mStep = eStep::GameReady;
			mScoreLabel->GetComponent<r2component::LabelComponent>()->SetString( r2utility::StringBuilder::Build( "0" ) );
			mMaxNumberLabel->GetComponent<r2component::LabelComponent>()->SetString( r2utility::StringBuilder::Build( "0" ) );
			mGameOverNode->SetVisible( false );
			break;

		case eStep::GameReady:
		{
			// Make 2 Number
			for( int i = 0; 2 > i; ++i )
			{
				mGameProcessor.AddNumber( 2u, 2u );
			}

			mStep = eStep::GameStart;
		}
		break;

		case eStep::GameStart:
			// Show Stage, On Input
			mStageViewComponent->UpdateView();
			mStageViewComponent->GetOwnerNode().SetVisible( true );
			mStep = eStep::GameUpdate;
			break;

		case eStep::GameUpdate:
		{
			// Input Process, Game End Check
			r2::Direction4::eState input_direction = r2::Direction4::eState::None;
			if( mKeyboardInputListener.IsPushed( 1 ) ) // A
			{
				input_direction = r2::Direction4::eState::Left;
			}
			else if( mKeyboardInputListener.IsPushed( 2 ) ) // D
			{
				input_direction = r2::Direction4::eState::Right;
			}
			else if( mKeyboardInputListener.IsPushed( 3 ) ) // S
			{
				input_direction = r2::Direction4::eState::Up;
			}
			else if( mKeyboardInputListener.IsPushed( 4 ) ) // W
			{
				input_direction = r2::Direction4::eState::Down;
			}

			if( r2::Direction4::eState::None != input_direction )
			{
				if( p2048mini::Config::GetNodeConfig().pivot )
				{
					mStageViewComponent4Debug->UpdateView();
				}

				if( !MoveNumber( input_direction ) )
				{
					if( mGameProcessor.IsGameClear() )
					{
						mStep = eStep::GameClear;
					}
					else
					{
						mStep = eStep::GameEnd;
					}
				}
			}
		}
		break;

		case eStep::GameEnd:
			mGameOverNode->SetVisible( true );
			mGameOverNode->GetComponent<r2component::ActionProcessComponent>()->StartAction();
			mStep = eStep::GameStop;
			break;
		}

		if( mKeyboardInputListener.IsPushed( 5 ) )
		{
			mStep = eStep::GameReset;
		}
		else if( mKeyboardInputListener.IsRelease( 0 ) )
		{
			r2utility::ClearCInputBuffer();
			mDirector.RequestAbort();
		}

		r2node::SceneNode::Update( delta_time );
	}

	bool GameScene::MoveNumber( const r2::Direction4::eState move_direction )
	{
		const auto move_result = mGameProcessor.Move( move_direction );
		if( move_result.has_moved )
		{
			mGameProcessor.AddNumber( 2u, 4u );
			mStageViewComponent->UpdateView();

			//
			// Score View Update
			//
			if( 0 < mGameProcessor.GetSum4Merged() )
			{
				mScoreLabel->GetComponent<r2component::LabelComponent>()->SetString( r2utility::StringBuilder::Build( "%d ( + %d )"
					, mGameProcessor.GetScore()
					, mGameProcessor.GetSum4Merged()
				) );

				mMaxNumberLabel->GetComponent<r2component::LabelComponent>()->SetString( r2utility::StringBuilder::Build( "%d"
					, mGameProcessor.GetMaxNumber()
				) );
			}
		}
		
		return !mGameProcessor.IsGameEnd();
	}
}