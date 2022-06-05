#include "p2048mini_TitleScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "r2bix/r2action_BlinkAction.h"
#include "r2bix/r2action_CallbackAction.h"
#include "r2bix/r2action_DelayAction.h"
#include "r2bix/r2action_RepeatAction.h"
#include "r2bix/r2action_SequenceAction.h"
#include "r2bix/r2base_Director.h"
#include "r2bix/r2component_ActionProcessComponent.h"
#include "r2bix/r2component_LabelComponent.h"
#include "r2bix/r2component_TextureFrameRenderComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2component_TransformComponent.h"
#include "r2bix/r2node_LabelNode.h"
#include "r2bix/r2node_SpriteNode.h"

#include "p2048mini/p2048mini_GameScene.h"
#include "p2048/p2048table_TextureFrameAnimationTable.h"
#include "p2048/p2048table_TextureTable.h"

#include "r2/r2_Random.h"

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

				{
					auto component = number_node->AddComponent<r2component::ActionProcessComponent>();

					auto repeat_action = r2action::RepeatAction::Create();
					{
						auto sequence_action = r2action::SequenceAction::Create();
						
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 3.f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.1f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 4.f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.1f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 1.f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.2f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 0.2f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.1f );
						}

						repeat_action->SetAction( std::move( sequence_action ) );
					}

					component->SetAction( std::move( repeat_action ) );
					component->StartAction();
				}
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

				{
					auto component = number_node->AddComponent<r2component::ActionProcessComponent>();

					auto repeat_action = r2action::RepeatAction::Create();
					{
						auto sequence_action = r2action::SequenceAction::Create();
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.2f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 1.2f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.2f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 0.2f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.1f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 0.3f );
						}
						{
							auto action = sequence_action->AddAction<r2action::BlinkAction>();
							action->SetTimeLimit( 0.4f );
						}
						{
							auto action = sequence_action->AddAction<r2action::DelayAction>();
							action->SetTimeLimit( 0.4f );
						}

						repeat_action->SetAction( std::move( sequence_action ) );
					}

					component->SetAction( std::move( repeat_action ) );
					component->StartAction();
				}
			}
			// Number 8
			{
				auto number_node = mSpriteNode->AddChild<r2node::SpriteNode>();
				number_node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "title_8" ) );
				number_node->mTransformComponent->SetPosition( 26, 0 );

				{
					auto component = number_node->AddComponent<r2component::ActionProcessComponent>();

					auto repeat_action = r2action::RepeatAction::Create();
					{
						auto sequence_action = r2action::SequenceAction::Create();
						{
							auto callback_action = sequence_action->AddAction<r2action::CallbackAction>();
							auto delay_action = sequence_action->AddAction<r2action::DelayAction>();
							auto blink_action = sequence_action->AddAction<r2action::BlinkAction>();
							
							callback_action->SetCallback( [delay_action, blink_action]()
							{
								delay_action->SetTimeLimit( r2::Random::GetFloat( 1.f, 3.f ) );
								blink_action->SetTimeLimit( r2::Random::GetFloat( 0.1f, 0.5f ) );
							} );
						}

						repeat_action->SetAction( std::move( sequence_action ) );
					}

					component->SetAction( std::move( repeat_action ) );
					component->StartAction();
				}
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
			{
				auto sequence_action = r2action::SequenceAction::Create();
				{
					auto action = sequence_action->AddAction<r2action::DelayAction>();
					action->SetTimeLimit( 1.1f );
				}
				{
					auto action = sequence_action->AddAction<r2action::BlinkAction>();
					action->SetTimeLimit( 0.5f );
				}

				repeat_action->SetAction( std::move( sequence_action ) );
			}

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
				mDirector.Setup( p2048mini::GameScene::Create( mDirector ) );
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}