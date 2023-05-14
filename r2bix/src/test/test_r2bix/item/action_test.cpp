#include "action_test.h"

#include <conio.h>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

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

#include "test/test_r2bix/TextureFrameAnimationTable4Test.h"
#include "test/test_r2bix/TextureTable4Test.h"
#include "test/Utility4Test.h"

#include "r2cm/r2cm_WindowUtility.h"


namespace action_test
{
	std::ostream& operator<<( std::ostream& o, const r2::PointInt& p )
	{
		o << "x : " << p.GetX() << "      " "y : " << p.GetY() << r2cm::linefeed;
		return o;
	}

	r2cm::iItem::TitleFunctionT TickActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TickAction";
		};
	}
	r2cm::iItem::DoFunctionT TickActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto tick_action = r2bix_action::TickAction::Create() );
				PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( tick_action ) ) );

				std::cout << r2cm::linefeed;

				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT DelayActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "DelayAction";
		};
	}
	r2cm::iItem::DoFunctionT DelayActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto move_by_action = r2bix_action::DelayAction::Create() );
				PROCESS_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.1f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}


	r2cm::iItem::TitleFunctionT SequenceActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "SequenceAction";
		};
	}
	r2cm::iItem::DoFunctionT SequenceActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );

				std::cout << r2cm::linefeed;

				{
					DECLARATION_MAIN( auto tick_action = sequence_action->AddAction<r2bix_action::TickAction>() );
					PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				std::cout << r2cm::linefeed;

				{
					DECLARATION_MAIN( auto tick_action = sequence_action->AddAction<r2bix_action::TickAction>() );
					PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( sequence_action ) ) );

				std::cout << r2cm::linefeed;

				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT MoveByActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MoveByAction";
		};
	}
	r2cm::iItem::DoFunctionT MoveByActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto move_by_action = r2bix_action::MoveByAction::Create() );
				PROCESS_MAIN( move_by_action->SetMoveAmount( { 5, 5 } ) );
				PROCESS_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2cm::split;

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2cm::linefeed;

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2cm::linefeed;

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_FALSE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2::PointInt( 6, 7 ), node->mTransformComponent->GetPosition() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT MoveToActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MoveToAction";
		};
	}
	r2cm::iItem::DoFunctionT MoveToActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto move_to_action = r2bix_action::MoveToAction::Create() );
				PROCESS_MAIN( move_to_action->SetEndPoint( { 5, 5 } ) );
				PROCESS_MAIN( move_to_action->SetTimeLimit( 1.5f ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( move_to_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2cm::split;

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2cm::linefeed;

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2cm::linefeed;

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_FALSE( component->IsRunning() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2::PointInt( 5, 5 ), node->mTransformComponent->GetPosition() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT RepeatActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "RepeatAction";
		};
	}
	r2cm::iItem::DoFunctionT RepeatActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto repeat_action = r2bix_action::RepeatAction::Create() );

				std::cout << r2cm::linefeed;

				DECLARATION_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );
				{
					std::cout << r2cm::linefeed;

					DECLARATION_MAIN( auto move_by_action_1 = sequence_action->AddAction<r2bix_action::MoveByAction>() );
					PROCESS_MAIN( move_by_action_1->SetMoveAmount( { 5, 5 } ) );
					PROCESS_MAIN( move_by_action_1->SetTimeLimit( 1.5f ) );

					std::cout << r2cm::linefeed;

					DECLARATION_MAIN( auto delay_action_1 = sequence_action->AddAction<r2bix_action::DelayAction>() );
					PROCESS_MAIN( delay_action_1->SetTimeLimit( 1.5f ) );

					std::cout << r2cm::linefeed;

					DECLARATION_MAIN( auto move_by_action_2 = sequence_action->AddAction<r2bix_action::MoveByAction>() );
					PROCESS_MAIN( move_by_action_2->SetMoveAmount( { -5, -5 } ) );
					PROCESS_MAIN( move_by_action_2->SetTimeLimit( 1.5f ) );

					std::cout << r2cm::linefeed;

					DECLARATION_MAIN( auto delay_action_2 = sequence_action->AddAction<r2bix_action::DelayAction>() );
					PROCESS_MAIN( delay_action_2->SetTimeLimit( 1.5f ) );
				}

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2cm::linefeed;

				const auto cursor_point = r2cm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2cm::WindowUtility::MoveCursorPoint( cursor_point );

					PROCESS_MAIN( component->Update( 0.0005f ) );
					std::cout << "X : " << node->mTransformComponent->GetPositionX() << "   Y : " << node->mTransformComponent->GetPositionY() << r2cm::linefeed;

					if( _kbhit() )
					{
						break;
					}
				}
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT BlinkActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "BlinkAction";
		};
	}
	r2cm::iItem::DoFunctionT BlinkActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto repeat_action = r2bix_action::RepeatAction::Create() );

				std::cout << r2cm::linefeed;
				{
					DECLARATION_MAIN( auto sequence_action = r2bix_action::SequenceAction::Create() );

					std::cout << r2cm::linefeed;

					{
						DECLARATION_MAIN( auto action = sequence_action->AddAction<r2bix_action::BlinkAction>() );
						PROCESS_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					std::cout << r2cm::linefeed;

					{
						DECLARATION_MAIN( auto action = sequence_action->AddAction<r2bix_action::DelayAction>() );
						PROCESS_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					std::cout << r2cm::linefeed;

					PROCESS_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );
				}

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2cm::linefeed;

				const auto cursor_point = r2cm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2cm::WindowUtility::MoveCursorPoint( cursor_point );

					PROCESS_MAIN( component->Update( 0.0001f ) );
					std::cout << "Visible : " << node->IsVisible() << r2cm::linefeed;

					if( _kbhit() )
					{
						break;
					}
				}
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT CallbackActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "CallbackAction";
		};
	}
	r2cm::iItem::DoFunctionT CallbackActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto repeat_action = r2bix_action::CallbackAction::Create() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( repeat_action->SetCallback( []() { std::cout << "Call Test Callback" << r2cm::linefeed; } ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT AnimationRequestActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "AnimationRequestAction";
		};
	}
	r2cm::iItem::DoFunctionT AnimationRequestActionTest::GetDoFunction() const
	{
		return[]()->r2cm::eItemLeaveAction
		{
			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );
			DECLARATION_SUB( auto node = r2bix_node::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 1 ) );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto tfrc = node->AddComponent<r2bix_component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto tfac = node->AddComponent<r2bix_component::TextureFrameAnimationComponent>() );
				PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
			}

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2bix_component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto action = r2bix_action::AnimationRequestAction::Create() );
				PROCESS_MAIN( action->SetAnimationIndex( r2bix_animation::eIndex::Run_1 ) );
				PROCESS_MAIN( action->SetOrder( r2bix_action::AnimationRequestAction::eOrder::PlayOnce ) );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( action ) ) );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2cm::linefeed;

				const auto cursor_point = r2cm::WindowUtility::GetCursorPoint();
				while( true )
				{
					r2cm::WindowUtility::MoveCursorPoint( cursor_point );

					PROCESS_MAIN( node->Update( 0.001f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

					std::cout << "Action Process Running : " << node->GetComponent<r2bix_component::ActionProcessComponent>()->IsRunning() << r2cm::linefeed;
					std::cout << "Animation Running : " << node->GetComponent<r2bix_component::TextureFrameAnimationComponent>()->IsRunning() << r2cm::linefeed2;

					r2bix_helper::Printer4Texture::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}