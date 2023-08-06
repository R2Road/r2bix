#include "action_test.h"

#include <conio.h>

#include "r2bix/r2bix_action_AnimationRequestAction.h"
#include "r2bix/r2bix_action_BlinkAction.h"
#include "r2bix/r2bix_action_CallbackAction.h"
#include "r2bix/r2bix_action_DelayAction.h"
#include "r2bix/r2bix_action_MoveByAction.h"
#include "r2bix/r2bix_action_MoveToAction.h"
#include "r2bix/r2bix_action_RepeatAction.h"
#include "r2bix/r2bix_action_SequenceAction.h"
#include "r2bix/r2bix_action_TickAction.h"
#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_node_Node.h"
#include "r2bix/r2bix_component_ActionProcessComponent.h"
#include "r2bix/r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix/r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix/r2bix_component_TransformComponent.h"
#include "r2bix/r2bix_render_Camera.h"
#include "r2bix/r2bix_render_Texture.h"
#include "r2bix/r2bix_render_TextureFrame.h"
#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

#include "test/test_r2bix/TextureFrameAnimationTable4Test.h"
#include "test/test_r2bix/TextureTable4Test.h"



namespace action_test
{
	std::ostream& operator<<( std::ostream& o, const r2::PointInt& p )
	{
		o << "x : " << p.GetX() << "      " "y : " << p.GetY() << r2tm::linefeed;
		return o;
	}

	r2tm::TitleFunctionT TickActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TickAction";
		};
	}
	r2tm::DoFunctionT TickActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECLARATION_MAIN( auto tick_action = r2bix_action::TickAction::Create() );
				PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( tick_action ) ) );

				LF();

				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT DelayActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "DelayAction";
		};
	}
	r2tm::DoFunctionT DelayActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECLARATION_MAIN( auto move_by_action = r2bix_action::DelayAction::Create() );
				PROCESS_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.1f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}


	r2tm::TitleFunctionT SequenceActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "SequenceAction";
		};
	}
	r2tm::DoFunctionT SequenceActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECLARATION_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );

				LF();

				{
					DECLARATION_MAIN( auto tick_action = sequence_action->AddAction<r2bix_action::TickAction>() );
					PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				LF();

				{
					DECLARATION_MAIN( auto tick_action = sequence_action->AddAction<r2bix_action::TickAction>() );
					PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				LF();

				PROCESS_MAIN( component->SetAction( std::move( sequence_action ) ) );

				LF();

				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT MoveByActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MoveByAction";
		};
	}
	r2tm::DoFunctionT MoveByActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECLARATION_MAIN( auto move_by_action = r2bix_action::MoveByAction::Create() );
				PROCESS_MAIN( move_by_action->SetMoveAmount( 5, 5 ) );
				PROCESS_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				LF();

				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_FALSE( component->IsRunning() );

				LF();

				EXPECT_EQ( r2::PointInt( 6, 7 ), node->mTransformComponent->GetPosition() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT MoveToActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MoveToAction";
		};
	}
	r2tm::DoFunctionT MoveToActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECLARATION_MAIN( auto move_to_action = r2bix_action::MoveToAction::Create() );
				PROCESS_MAIN( move_to_action->SetEndPoint( 5, 5 ) );
				PROCESS_MAIN( move_to_action->SetTimeLimit( 1.5f ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( move_to_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				LF();

				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_FALSE( component->IsRunning() );

				LF();

				EXPECT_EQ( r2::PointInt( 5, 5 ), node->mTransformComponent->GetPosition() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT RepeatActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "RepeatAction";
		};
	}
	r2tm::DoFunctionT RepeatActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECLARATION_MAIN( auto repeat_action = r2bix_action::RepeatAction::Create() );

				LF();

				DECLARATION_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );
				{
					LF();

					DECLARATION_MAIN( auto move_by_action_1 = sequence_action->AddAction<r2bix_action::MoveByAction>() );
					PROCESS_MAIN( move_by_action_1->SetMoveAmount( 5, 5 ) );
					PROCESS_MAIN( move_by_action_1->SetTimeLimit( 1.5f ) );

					LF();

					DECLARATION_MAIN( auto delay_action_1 = sequence_action->AddAction<r2bix_action::DelayAction>() );
					PROCESS_MAIN( delay_action_1->SetTimeLimit( 1.5f ) );

					LF();

					DECLARATION_MAIN( auto move_by_action_2 = sequence_action->AddAction<r2bix_action::MoveByAction>() );
					PROCESS_MAIN( move_by_action_2->SetMoveAmount( -5, -5 ) );
					PROCESS_MAIN( move_by_action_2->SetTimeLimit( 1.5f ) );

					LF();

					DECLARATION_MAIN( auto delay_action_2 = sequence_action->AddAction<r2bix_action::DelayAction>() );
					PROCESS_MAIN( delay_action_2->SetTimeLimit( 1.5f ) );
				}

				LF();

				PROCESS_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );

				LF();

				const auto cursor_point = r2tm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowUtility::MoveCursorPoint( cursor_point );

					PROCESS_MAIN( component->Update( 0.0005f ) );
					std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

					if( _kbhit() )
					{
						break;
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT BlinkActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "BlinkAction";
		};
	}
	r2tm::DoFunctionT BlinkActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECLARATION_MAIN( auto repeat_action = r2bix_action::RepeatAction::Create() );

				LF();
				{
					DECLARATION_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );

					LF();

					{
						DECLARATION_MAIN( auto action = sequence_action->AddAction<r2bix_action::BlinkAction>() );
						PROCESS_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					LF();

					{
						DECLARATION_MAIN( auto action = sequence_action->AddAction<r2bix_action::DelayAction>() );
						PROCESS_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					LF();

					PROCESS_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );
				}

				LF();

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );

				LF();

				const auto cursor_point = r2tm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowUtility::MoveCursorPoint( cursor_point );

					PROCESS_MAIN( component->Update( 0.0001f ) );
					std::cout << "Visible : " << node->IsVisible() << r2tm::linefeed;

					if( _kbhit() )
					{
						break;
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CallbackActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "CallbackAction";
		};
	}
	r2tm::DoFunctionT CallbackActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECLARATION_MAIN( auto repeat_action = r2bix_action::CallbackAction::Create() );

				LF();

				PROCESS_MAIN( repeat_action->SetCallback( []() { std::cout << "Call Test Callback" << r2tm::linefeed; } ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );

				LF();

				PROCESS_MAIN( component->Update( 0.f ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT AnimationRequestActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "AnimationRequestAction";
		};
	}
	r2tm::DoFunctionT AnimationRequestActionTest::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 14, 10 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 1 ) );

			LS();

			{
				DECLARATION_MAIN( auto tfrc = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto tfac = node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );
				PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
			}

			LS();

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECLARATION_MAIN( auto action = r2bix_action::AnimationRequestAction::Create() );
				PROCESS_MAIN( action->SetAnimationIndex( r2bix_animation::eIndex::Run_1 ) );
				PROCESS_MAIN( action->SetOrder( r2bix_action::AnimationRequestAction::eOrder::PlayOnce ) );

				LF();

				PROCESS_MAIN( component->SetAction( std::move( action ) ) );
			}

			LS();

			{
				PROCESS_MAIN( component->StartAction() );

				LF();

				const auto cursor_point = r2tm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowUtility::MoveCursorPoint( cursor_point );

					PROCESS_MAIN( node->Update( 0.001f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

					std::cout << "Action Process Running : " << node->GetComponent<r2bix_component::ActionProcessComponent>()->IsRunning() << r2tm::linefeed;
					std::cout << "Animation Running : " << node->GetComponent<r2bix_component::TextureFrameAnimationComponent>()->IsRunning() << r2tm::linefeed2;

					r2bix_helper::Printer4Texture::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}