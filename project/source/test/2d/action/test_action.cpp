#include "test_action.h"

#include <conio.h>

#include "r2bix_action_AnimationRequestAction.h"
#include "r2bix_action_BlinkAction.h"
#include "r2bix_action_CallbackAction.h"
#include "r2bix_action_DelayAction.h"
#include "r2bix_action_MoveByAction.h"
#include "r2bix_action_MoveToAction.h"
#include "r2bix_action_RepeatAction.h"
#include "r2bix_action_SequenceAction.h"
#include "r2bix_action_TickAction.h"
#include "r2bix_Director.h"
#include "r2bix_node_Node.h"
#include "r2bix_component_ActionProcessComponent.h"
#include "r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix_component_TransformComponent.h"
#include "r2bix_Camera.h"
#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"
#include "helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "test/2d/TextureFrameAnimationTable4Test.h"
#include "test/2d/TextureTable4Test.h"



namespace test_action
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECL_MAIN( auto tick_action = r2bix_action::TickAction::Create() );
				PROC_MAIN( tick_action->SetTickLimit( 1 ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( tick_action ) ) );

				LF();

				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECL_MAIN( auto move_by_action = r2bix_action::DelayAction::Create() );
				PROC_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.1f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECL_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );

				LF();

				{
					DECL_MAIN( auto tick_action = sequence_action->AddAction<r2bix_action::TickAction>() );
					PROC_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				LF();

				{
					DECL_MAIN( auto tick_action = sequence_action->AddAction<r2bix_action::TickAction>() );
					PROC_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				LF();

				PROC_MAIN( component->SetAction( std::move( sequence_action ) ) );

				LF();

				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.f ) );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECL_MAIN( auto move_by_action = r2bix_action::MoveByAction::Create() );
				PROC_MAIN( move_by_action->SetMoveAmount( 5, 5 ) );
				PROC_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				LF();

				PROC_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				EXPECT_FALSE( component->HasAction() );

				LF();

				DECL_MAIN( auto move_to_action = r2bix_action::MoveToAction::Create() );
				PROC_MAIN( move_to_action->SetEndPoint( 5, 5 ) );
				PROC_MAIN( move_to_action->SetTimeLimit( 1.5f ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( move_to_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			LS();

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				LF();

				PROC_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2tm::linefeed;

				LF();

				PROC_MAIN( component->Update( 0.7f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECL_MAIN( auto repeat_action = r2bix_action::RepeatAction::Create() );

				LF();

				DECL_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );
				{
					LF();

					DECL_MAIN( auto move_by_action_1 = sequence_action->AddAction<r2bix_action::MoveByAction>() );
					PROC_MAIN( move_by_action_1->SetMoveAmount( 5, 5 ) );
					PROC_MAIN( move_by_action_1->SetTimeLimit( 1.5f ) );

					LF();

					DECL_MAIN( auto delay_action_1 = sequence_action->AddAction<r2bix_action::DelayAction>() );
					PROC_MAIN( delay_action_1->SetTimeLimit( 1.5f ) );

					LF();

					DECL_MAIN( auto move_by_action_2 = sequence_action->AddAction<r2bix_action::MoveByAction>() );
					PROC_MAIN( move_by_action_2->SetMoveAmount( -5, -5 ) );
					PROC_MAIN( move_by_action_2->SetTimeLimit( 1.5f ) );

					LF();

					DECL_MAIN( auto delay_action_2 = sequence_action->AddAction<r2bix_action::DelayAction>() );
					PROC_MAIN( delay_action_2->SetTimeLimit( 1.5f ) );
				}

				LF();

				PROC_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );

				LF();

				const auto cursor_point = r2tm::WindowsUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowsUtility::MoveCursorPoint( cursor_point );

					PROC_MAIN( component->Update( 0.0005f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECL_MAIN( auto repeat_action = r2bix_action::RepeatAction::Create() );

				LF();
				{
					DECL_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );

					LF();

					{
						DECL_MAIN( auto action = sequence_action->AddAction<r2bix_action::BlinkAction>() );
						PROC_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					LF();

					{
						DECL_MAIN( auto action = sequence_action->AddAction<r2bix_action::DelayAction>() );
						PROC_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					LF();

					PROC_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );
				}

				LF();

				PROC_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );

				LF();

				const auto cursor_point = r2tm::WindowsUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowsUtility::MoveCursorPoint( cursor_point );

					PROC_MAIN( component->Update( 0.0001f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECL_MAIN( auto repeat_action = r2bix_action::CallbackAction::Create() );

				LF();

				PROC_MAIN( repeat_action->SetCallback( []() { std::cout << "Call Test Callback" << r2tm::linefeed; } ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );

				LF();

				PROC_MAIN( component->Update( 0.f ) );
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

			DECL_SUB( r2bix::Camera camera( 0, 0, 14, 10 ) );
			DECL_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECL_SUB( r2bix::Director dummy_director( {} ) );
			DECL_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROC_SUB( node->mTransformComponent->SetPosition( 0, 1 ) );

			LS();

			{
				DECL_MAIN( auto tfrc = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
				DECL_MAIN( auto tfac = node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );
				PROC_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
				PROC_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
			}

			LS();

			DECL_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			LS();

			{
				DECL_MAIN( auto action = r2bix_action::AnimationRequestAction::Create() );
				PROC_MAIN( action->SetAnimationIndex( r2bix_animation::eIndex::Run_1 ) );
				PROC_MAIN( action->SetOrder( r2bix_action::AnimationRequestAction::eOrder::PlayOnce ) );

				LF();

				PROC_MAIN( component->SetAction( std::move( action ) ) );
			}

			LS();

			{
				PROC_MAIN( component->StartAction() );

				LF();

				const auto cursor_point = r2tm::WindowsUtility::GetCursorPoint();
				while( true )
				{
					r2tm::WindowsUtility::MoveCursorPoint( cursor_point );

					PROC_MAIN( node->Update( 0.001f ) );
					PROC_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

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