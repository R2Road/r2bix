#include "pch.h"
#include "action_test.h"

#include <conio.h>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "action/r2action_AnimationRequestAction.h"
#include "action/r2action_BlinkAction.h"
#include "action/r2action_CallbackAction.h"
#include "action/r2action_DelayAction.h"
#include "action/r2action_MoveByAction.h"
#include "action/r2action_RepeatAction.h"
#include "action/r2action_SequenceAction.h"
#include "action/r2action_TickAction.h"
#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_ActionProcessComponent.h"
#include "component/r2component_TextureFrameAnimationComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

#include "test/test_r2bix/TextureFrameAnimationTable4Test.h"
#include "test/test_r2bix/TextureTable4Test.h"
#include "test/Utility4Test.h"

#include "utility/r2utility_WindowUtil.h"

namespace action_test
{
	r2cm::iItem::TitleFuncT TickActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TickAction";
		};
	}
	r2cm::iItem::DoFuncT TickActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( auto tick_action = r2action::TickAction::Create() );
				PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( tick_action ) ) );

				std::cout << r2::linefeed;

				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT DelayActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "DelayAction";
		};
	}
	r2cm::iItem::DoFuncT DelayActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( auto move_by_action = r2action::DelayAction::Create() );
				PROCESS_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.1f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}


	r2cm::iItem::TitleFuncT SequenceActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "SequenceAction";
		};
	}
	r2cm::iItem::DoFuncT SequenceActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( auto sequence_action = r2action::SequenceAction::Create() );

				std::cout << r2::linefeed;

				{
					DECLARATION_MAIN( auto tick_action = sequence_action->AddAction<r2action::TickAction>() );
					PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				std::cout << r2::linefeed;

				{
					DECLARATION_MAIN( auto tick_action = sequence_action->AddAction<r2action::TickAction>() );
					PROCESS_MAIN( tick_action->SetTickLimit( 1 ) );
				}

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( sequence_action ) ) );

				std::cout << r2::linefeed;

				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
				EXPECT_FALSE( component->IsRunning() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT MoveByActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "MoveByAction";
		};
	}
	r2cm::iItem::DoFuncT MoveByActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 1, 2 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				EXPECT_FALSE( component->HasAction() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( auto move_by_action = r2action::MoveByAction::Create() );
				PROCESS_MAIN( move_by_action->SetMoveAmount( { 5, 5 } ) );
				PROCESS_MAIN( move_by_action->SetTimeLimit( 1.5f ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( move_by_action ) ) );
				EXPECT_TRUE( component->HasAction() );
			}

			std::cout << r2::split;

			{
				EXPECT_EQ( r2::PointInt( 1, 2 ), node->mTransformComponent->GetPosition() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->StartAction() );
				EXPECT_TRUE( component->IsRunning() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPosition().GetX() << "   Y : " << node->mTransformComponent->GetPosition().GetY() << r2::linefeed;

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_TRUE( component->IsRunning() );
				std::cout << "X : " << node->mTransformComponent->GetPosition().GetX() << "   Y : " << node->mTransformComponent->GetPosition().GetY() << r2::linefeed;

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.7f ) );
				EXPECT_FALSE( component->IsRunning() );

				std::cout << r2::linefeed;

				EXPECT_EQ( r2::PointInt( 6, 7 ), node->mTransformComponent->GetPosition() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT RepeatActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "RepeatAction";
		};
	}
	r2cm::iItem::DoFuncT RepeatActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto repeat_action = r2action::RepeatAction::Create() );

				std::cout << r2::linefeed;

				DECLARATION_MAIN( auto sequence_action = r2action::SequenceAction::Create() );
				{
					std::cout << r2::linefeed;

					DECLARATION_MAIN( auto move_by_action_1 = sequence_action->AddAction<r2action::MoveByAction>() );
					PROCESS_MAIN( move_by_action_1->SetMoveAmount( { 5, 5 } ) );
					PROCESS_MAIN( move_by_action_1->SetTimeLimit( 1.5f ) );

					std::cout << r2::linefeed;

					DECLARATION_MAIN( auto delay_action_1 = sequence_action->AddAction<r2action::DelayAction>() );
					PROCESS_MAIN( delay_action_1->SetTimeLimit( 1.5f ) );

					std::cout << r2::linefeed;

					DECLARATION_MAIN( auto move_by_action_2 = sequence_action->AddAction<r2action::MoveByAction>() );
					PROCESS_MAIN( move_by_action_2->SetMoveAmount( { -5, -5 } ) );
					PROCESS_MAIN( move_by_action_2->SetTimeLimit( 1.5f ) );

					std::cout << r2::linefeed;

					DECLARATION_MAIN( auto delay_action_2 = sequence_action->AddAction<r2action::DelayAction>() );
					PROCESS_MAIN( delay_action_2->SetTimeLimit( 1.5f ) );
				}

				std::cout << r2::linefeed;

				PROCESS_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2::linefeed;

				const auto cursor_point = r2utility::GetCursorPoint();
				while( true )
				{
					r2utility::SetCursorPoint( cursor_point );

					PROCESS_MAIN( component->Update( 0.0005f ) );
					std::cout << "X : " << node->mTransformComponent->GetPosition().GetX() << "   Y : " << node->mTransformComponent->GetPosition().GetY() << r2::linefeed;

					if( _kbhit() )
					{
						break;
					}
				}
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT BlinkActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "BlinkAction";
		};
	}
	r2cm::iItem::DoFuncT BlinkActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto repeat_action = r2action::RepeatAction::Create() );

				std::cout << r2::linefeed;
				{
					DECLARATION_MAIN( auto sequence_action = r2action::SequenceAction::Create() );

					std::cout << r2::linefeed;

					{
						DECLARATION_MAIN( auto action = sequence_action->AddAction<r2action::BlinkAction>() );
						PROCESS_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					std::cout << r2::linefeed;

					{
						DECLARATION_MAIN( auto action = sequence_action->AddAction<r2action::DelayAction>() );
						PROCESS_MAIN( action->SetTimeLimit( 0.5f ) );
					}

					std::cout << r2::linefeed;

					PROCESS_MAIN( repeat_action->SetAction( std::move( sequence_action ) ) );
				}

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2::linefeed;

				const auto cursor_point = r2utility::GetCursorPoint();
				while( true )
				{
					r2utility::SetCursorPoint( cursor_point );

					PROCESS_MAIN( component->Update( 0.0001f ) );
					std::cout << "Visible : " << node->IsVisible() << r2::linefeed;

					if( _kbhit() )
					{
						break;
					}
				}
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT CallbackActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "CallbackAction";
		};
	}
	r2cm::iItem::DoFuncT CallbackActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 0 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto repeat_action = r2action::CallbackAction::Create() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( repeat_action->SetCallback( []() { std::cout << "Call Test Callback" << r2::linefeed; } ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( repeat_action ) ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->Update( 0.f ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT AnimationRequestActionTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "AnimationRequestAction";
		};
	}
	r2cm::iItem::DoFuncT AnimationRequestActionTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			TextureTable4Test::GetInstance().Load();
			TextureFrameAnimationTable4Test::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 0, 0 }, { 14, 10 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2base::Director dummy_director );
			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 0, 1 ) );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto tfrc = node->AddComponent<r2component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto tfac = node->AddComponent<r2component::TextureFrameAnimationComponent>() );
				PROCESS_MAIN( tfac->SetTextureFrameRenderComponent( tfrc ) );
				PROCESS_MAIN( tfac->LoadAnimation( TextureFrameAnimationTable4Test::GetInstance().Get( 1 ) ) );
			}

			std::cout << r2::split;

			DECLARATION_MAIN( auto component = node->AddComponent<r2component::ActionProcessComponent>() );
			EXPECT_NE( nullptr, component );
			EXPECT_FALSE( component->HasAction() );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto action = r2action::AnimationRequestAction::Create() );
				PROCESS_MAIN( action->SetAnimationIndex( r2animation::eIndex::Run_1 ) );
				PROCESS_MAIN( action->SetOrder( r2action::AnimationRequestAction::eOrder::PlayOnce ) );

				std::cout << r2::linefeed;

				PROCESS_MAIN( component->SetAction( std::move( action ) ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( component->StartAction() );

				std::cout << r2::linefeed;

				const auto cursor_point = r2utility::GetCursorPoint();
				while( true )
				{
					r2utility::SetCursorPoint( cursor_point );

					PROCESS_MAIN( node->Update( 0.001f ) );
					PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

					std::cout << "Action Process Running : " << node->GetComponent<r2component::ActionProcessComponent>()->IsRunning() << r2::linefeed;
					std::cout << "Animation Running : " << node->GetComponent<r2component::TextureFrameAnimationComponent>()->IsRunning() << r2::linefeed2;

					Utility4Test::DrawTexture( render_target );

					if( _kbhit() )
					{
						break;
					}
				}
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}