#include "p2048_GameComponent.h"

#include "r2utility_StringBuilder.h"
#include "r2bix_Director.h"
#include "r2bix_node_Node.h"
#include "r2bix_component_ActionProcessComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_utility_InputUtil.h"

#include "p2048_Config.h"
#include "p2048_StageViewComponent.h"

namespace p2048
{
	GameComponent::GameComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<GameComponent>( owner_node )
		, mStep( eStep::GameReady )
		, mStage( 4u, 4u )
		, mGameProcessor( &mStage )
		, mStageViewComponent( nullptr )
		, mStageViewComponent4History( nullptr )

		, mMaxNumberLabel( nullptr )
		, mTotalScoreLabel( nullptr )
		, mRecentScoreLabel( nullptr )

		, mYouWinNode( nullptr )
		, mGameOverNode( nullptr )

		, mKeyboardInputListener( {
			0x1B		// esc
			, 0x41		// a - left
			, 0x44		// d - right
			, 0x53		// s - down
			, 0x57		// w - up
			, 0x52		// r - reset
			, 0x09		// tab - history
		} )
	{
		GetOwnerNode().GetDirector().AddInputListener( &mKeyboardInputListener );
	}
	GameComponent::~GameComponent()
	{
		GetOwnerNode().GetDirector().RemoveInputListener( &mKeyboardInputListener );
	}

	void GameComponent::Update( const float delta_time )
	{
		switch( mStep )
		{
		case eStep::GameReset:
			mStep = eStep::GameReady;
			mGameProcessor.Reset();

			mStageViewComponent->GetOwnerNode().SetVisible( false );
			mMaxNumberLabel->GetComponent<r2bix_component::LabelSComponent>()->SetString( r2utility::StringBuilder::Build( "0" ) );
			mTotalScoreLabel->GetComponent<r2bix_component::LabelSComponent>()->SetString( r2utility::StringBuilder::Build( "0" ) );
			mRecentScoreLabel->GetComponent<r2bix_component::LabelSComponent>()->SetString( r2utility::StringBuilder::Build( "0" ) );

			mYouWinNode->SetVisible( false );
			mGameOverNode->SetVisible( false );
			break;

		case eStep::GameReady:
		{
			mStageViewComponent4History->UpdateView();

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
			r2::Direction4Sequential::eState input_direction = r2::Direction4Sequential::eState::NONE;
			if( mKeyboardInputListener.IsPushed( 1 ) ) // A
			{
				input_direction = r2::Direction4Sequential::eState::Left;
			}
			else if( mKeyboardInputListener.IsPushed( 2 ) ) // D
			{
				input_direction = r2::Direction4Sequential::eState::Right;
			}
			else if( mKeyboardInputListener.IsPushed( 3 ) ) // S
			{
				input_direction = r2::Direction4Sequential::eState::Up;
			}
			else if( mKeyboardInputListener.IsPushed( 4 ) ) // W
			{
				input_direction = r2::Direction4Sequential::eState::Down;
			}

			if( r2::Direction4Sequential::eState::NONE != input_direction )
			{
				mStageViewComponent4History->UpdateView();

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
			mGameOverNode->GetComponent<r2bix_component::ActionProcessComponent>()->StartAction();
			mStep = eStep::GameStop;
			break;

		case eStep::GameClear:
			mYouWinNode->SetVisible( true );
			mYouWinNode->GetComponent<r2bix_component::ActionProcessComponent>()->StartAction();
			mStep = eStep::GameStop;
			break;
		}

		if( mKeyboardInputListener.IsPushed( 6 ) )
		{
			mStageViewComponent4History->GetOwnerNode().SetVisible( true );
		}
		else if( mKeyboardInputListener.IsRelease( 6 ) )
		{
			mStageViewComponent4History->GetOwnerNode().SetVisible( false );
		}

		if( mKeyboardInputListener.IsPushed( 5 ) )
		{
			mStep = eStep::GameReset;
		}
		else if( mKeyboardInputListener.IsRelease( 0 ) )
		{
			r2bix_utility::ClearCInputBuffer();
			GetOwnerNode().GetDirector().RequestAbort();
		}

		r2bix_component::iComponent::Update( delta_time );
	}

	bool GameComponent::MoveNumber( const r2::Direction4Sequential::eState move_direction )
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
				mMaxNumberLabel->GetComponent<r2bix_component::LabelSComponent>()->SetString( r2utility::StringBuilder::Build( "%d"
					, mGameProcessor.GetMaxNumber()
				) );

				mTotalScoreLabel->GetComponent<r2bix_component::LabelSComponent>()->SetString( r2utility::StringBuilder::Build( "%d"
					, mGameProcessor.GetScore()
				) );
				
				mRecentScoreLabel->GetComponent<r2bix_component::LabelSComponent>()->SetString( r2utility::StringBuilder::Build( "+ %d"
					, mGameProcessor.GetSum4Merged()
				) );
			}
		}

		return !mGameProcessor.IsGameEnd();
	}
}