#include "pch.h"
#include "p2048mini_GameScene.h"

#include <cassert>
#include <conio.h>
#include <numeric>

#include "base/r2base_Director.h"
#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_CustomTextureNode.h"
#include "node/r2node_PivotNode.h"

#include "p2048mini_Stage.h"
#include "p2048mini_StageViewComponent.h"
#include "p2048mini_StageViewNode.h"
#include "p2048minitable_TextureTable.h"

#include "r2/r2_Random.h"
#include "utility/r2utility_InputUtil.h"

namespace p2048mini
{
	GameScene::GameScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mStep( eStep::GameReady )
		, mStage( 4u, 4u )
		, mStageViewComponent( nullptr )

		, mKeyboardInputCollector()
		, mKeyboardInputListener( {
			0x1B		// esc
			, 0x41		// a
			, 0x44		// d
			, 0x53		// s
			, 0x57		// w
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
			auto node = AddChild<r2node::CustomTextureNode>();
			node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 37, 17, '=' );
			node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
			node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect();

			node->mTransformComponent->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f ) - ( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->GetHeight() * 0.5f )
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
		mKeyboardInputCollector.Collect();
		mKeyboardInputListener.Update();

		switch( mStep )
		{
		case eStep::GameReady:
		{
			// Make 2 Number
			for( int i = 0; 2 > i; ++i )
			{
				AddNumber();
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
				if( !MoveNumber( input_direction ) )
				{
					mStep = eStep::GameEnd;
				}
			}
		}
		break;

		case eStep::GameEnd:
			// Do Something
			break;
		}

		if( mKeyboardInputListener.IsRelease( 0 ) )
		{
			r2utility::ClearCInputBuffer();
			mDirector.RequestAbort();
		}

		r2node::SceneNode::Update( delta_time );
	}

	void GameScene::AddNumber()
	{
		const auto target_space = r2::Random::GetInt( 0, mStage.GetEmptySpaceCount() - 1 );
		int current_space = 0;
		do
		{
			if( target_space <= current_space )
			{
				if( 0 == mStage.Get( current_space ) )
				{
					mStage.Add( current_space, 32 );
					break;
				}
			}

			++current_space;
		} while( true );
	}
	bool GameScene::MoveNumber( const r2::Direction4::eState move_direction )
	{
		if( mStage.Move( move_direction ) )
		{
			AddNumber();
			mStageViewComponent->UpdateView();
		}
		
		if( 0 == mStage.GetEmptySpaceCount() && false == mStage.IsMovable() )
		{
			// Game End
			return false;
		}
		else
		{
			return true;
		}
	}
}