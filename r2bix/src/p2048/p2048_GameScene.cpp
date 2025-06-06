#include "p2048_GameScene.h"

#include <numeric>

#include "r2bix_action_SequenceAction.h"
#include "r2bix_action_DelayAction.h"
#include "r2bix_action_MoveByAction.h"
#include "r2bix_action_MoveToAction.h"
#include "r2bix_component_ActionProcessComponent.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_Director.h"
#include "r2bix_node_CustomTextureNode.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_node_PivotNode.h"
#include "r2bix_node_SpriteNode.h"

#include "p2048_GameComponent.h"
#include "p2048_StageViewComponent.h"
#include "p2048_StageViewNode.h"
#include "p2048table_TextureTable.h"

#include "p2048_Config.h"

namespace p2048
{
	r2bix_node::NodeUp GameScene::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			// Table Load
			//
			p2048table::TextureTable::GetInstance().Load();

			//
			// Game Component
			//
			auto game_component = ret->AddComponent<p2048::GameComponent>();

			//
			// Stage View
			//
			{
				auto stage_view_node = ret->AddChild<p2048::StageViewNode>( 1 );
				stage_view_node->SetVisible( false );

				auto stage_view_component = stage_view_node->GetComponent<p2048::StageViewComponent>();
				stage_view_component->Setup( game_component->GetStage() );

				stage_view_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					( director.GetScreenSize().GetWidth() * 0.5f ) - ( stage_view_component->GetWidth() * 0.5f )
					, ( director.GetScreenSize().GetHeight() * 0.5f ) - ( stage_view_component->GetHeight() * 0.5f )
				);

				//
				//
				//
				game_component->SetStageViewComponent( stage_view_component );
			}
			//
			// History View
			//
			{
				auto stage_view_node = ret->AddChild<p2048::StageViewNode>( 2 );
				stage_view_node->SetVisible( false );

				auto stage_view_component_4debug = stage_view_node->GetComponent<p2048::StageViewComponent>();
				stage_view_component_4debug->Setup( game_component->GetStage() );

				stage_view_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					( director.GetScreenSize().GetWidth() * 0.5f ) - ( stage_view_component_4debug->GetWidth() * 0.5f )
					, ( director.GetScreenSize().GetHeight() * 0.5f ) - ( stage_view_component_4debug->GetHeight() * 0.5f )
				);

				//
				//
				//
				game_component->SetStageViewComponent4History( stage_view_component_4debug );
			}

			const int score_label_x = 39;
			const int score_number_x = score_label_x + 10;

			//
			// Max Number
			//
			{
				auto label_node = ret->AddChild<r2bix_node::LabelSNode>();
				label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Max : " );
				label_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivot( 1.f, 0.f );
				label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( score_label_x, 9 );

				auto max_number_label_node = ret->AddChild<r2bix_node::LabelSNode>( 1 );
				max_number_label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "0" );
				max_number_label_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivot( 1.f, 0.f );
				max_number_label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( score_number_x, 9 );

				//
				//
				//
				game_component->SetMaxNumberLabel( max_number_label_node );
			}

			//
			// Score
			//
			{
				auto label_node = ret->AddChild<r2bix_node::LabelSNode>();
				label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Score : " );
				label_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivot( 1.f, 0.f );
				label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( score_label_x, 10 );

				auto total_score_label_node = ret->AddChild<r2bix_node::LabelSNode>( 1 );
				total_score_label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "0" );
				total_score_label_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivot( 1.f, 0.f );
				total_score_label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( score_number_x, 10 );

				//
				//
				//
				game_component->SetTotalScoreLabel( total_score_label_node );
			}

			//
			// Recent Score
			//
			{
				auto label_node = ret->AddChild<r2bix_node::LabelSNode>();
				label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Recent : " );
				label_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivot( 1.f, 0.f );
				label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( score_label_x, 11 );

				auto total_score_label_node = ret->AddChild<r2bix_node::LabelSNode>( 1 );
				total_score_label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "0" );
				total_score_label_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivot( 1.f, 0.f );
				total_score_label_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( score_number_x, 11 );

				//
				//
				//
				game_component->SetRecentScoreLabel( total_score_label_node );
			}

			//
			// Key Info
			//
			{
				auto sprite_node = ret->AddChild<r2bix_node::SpriteNode>();
				sprite_node->GetComponent<r2bix_component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "keyinfo_0" ) );
				sprite_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 23, 33 );
			}

			//
			// You Win
			//
			{
				auto you_win_node = ret->AddChild<r2bix_node::SpriteNode>( 2 );
				you_win_node->GetComponent<r2bix_component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "you_win_0" ) );
				you_win_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					( director.GetScreenSize().GetWidth() * 0.5f )
					, ( director.GetScreenSize().GetHeight() * 0.5f )
				);
				you_win_node->SetVisible( false );

				auto action_process_component = you_win_node->AddComponent<r2bix_component::ActionProcessComponent>();
				{
					auto sequence_action = r2bix_action::SequenceAction::Create();

					auto moveto_action = sequence_action->AddAction<r2bix_action::MoveToAction>();
					moveto_action->SetEndPoint( you_win_node->GetComponent<r2bix_component::TransformComponent>()->GetPosition() );
					moveto_action->SetTimeLimit( 0.f );

					auto delay_action = sequence_action->AddAction<r2bix_action::DelayAction>();
					delay_action->SetTimeLimit( 1.f );

					auto moveby_action = sequence_action->AddAction<r2bix_action::MoveByAction>();
					moveby_action->SetMoveAmount( r2::PointInt( 0, 17 ) );
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
				auto game_over_node = ret->AddChild<r2bix_node::SpriteNode>( 2 );
				game_over_node->GetComponent<r2bix_component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "game_over_0" ) );
				game_over_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					( director.GetScreenSize().GetWidth() * 0.5f )
					, ( director.GetScreenSize().GetHeight() * 0.5f )
				);
				game_over_node->SetVisible( false );

				auto action_process_component = game_over_node->AddComponent<r2bix_component::ActionProcessComponent>();
				{
					auto sequence_action = r2bix_action::SequenceAction::Create();

					auto moveto_action = sequence_action->AddAction<r2bix_action::MoveToAction>();
					moveto_action->SetEndPoint( game_over_node->GetComponent<r2bix_component::TransformComponent>()->GetPosition() );
					moveto_action->SetTimeLimit( 0.f );

					auto delay_action = sequence_action->AddAction<r2bix_action::DelayAction>();
					delay_action->SetTimeLimit( 1.f );

					auto moveby_action = sequence_action->AddAction<r2bix_action::MoveByAction>();
					moveby_action->SetMoveAmount( r2::PointInt( 0, 17 ) );
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
			if( p2048::Config::GetNodeConfig().pivot )
			{
				//
				//
				//
				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() );
				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( director.GetScreenSize().GetWidth() - 1, 0 );
				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( director.GetScreenSize().GetWidth() - 1, director.GetScreenSize().GetHeight() - 1 );
				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( 0, director.GetScreenSize().GetHeight() - 1 );

				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( director.GetScreenSize().GetWidth() * 0.5f, director.GetScreenSize().GetHeight() * 0.5f );
			}



			//
			// Ȱ��ȭ
			//
			game_component->Activate();
		}

		return ret;
	}
}