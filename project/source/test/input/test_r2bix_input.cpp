#include "test_r2bix_input.hpp"

#include <algorithm>

#include "r2bix_input_InputManager.h"
#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

#include "r2_rect_int.hpp"
#include "r2_fps_timer.hpp"
#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

namespace test_input
{
	r2tm::TitleFunctionT InputManager_Order1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "InputManager : Order 1";
		};
	}
	r2tm::DoFunctionT InputManager_Order1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUT_NOTE( "같은 Order 값이면 늦게 추가된 리스너가 목록의 앞으로 온다." );

			LS();

			DECL_MAIN( r2bix_input::InputManager m( 0, 0 ) );

			LS();

			{
				OUT_SUBJECT( "Mouse" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Mouse l_1( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_2( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_3( 1 ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Mouse().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Mouse().begin() ) ), &l_2 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Mouse().begin() ) ), &l_1 );

				LF();

				OUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Mouse() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			{
				OUT_SUBJECT( "Keyboard" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Keyboard l_1( 1, r2bix_input::eListenMode::Pass ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_2( 1, r2bix_input::eListenMode::Pass ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_3( 1, r2bix_input::eListenMode::Pass ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Keyboard().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Keyboard().begin() ) ), &l_2 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Keyboard().begin() ) ), &l_1 );

				LF();

				OUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Keyboard() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InputManager_Order2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "InputManager : Order 2";
		};
	}
	r2tm::DoFunctionT InputManager_Order2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUT_NOTE( "높은 Order 값을 가지면 목록의 앞으로 온다.");

			LS();

			DECL_MAIN( r2bix_input::InputManager m( 0, 0 ) );

			LS();

			{
				OUT_SUBJECT( "Mouse" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Mouse l_1( 2 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_2( 1 ) );
				DECL_MAIN( r2bix_input::Listener4Mouse l_3( 3 ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Mouse().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Mouse().begin() ) ), &l_1 );
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Mouse().begin() ) ), &l_2 );

				LF();

				OUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Mouse() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			{
				OUT_SUBJECT( "Keyboard" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Keyboard l_1( 2, r2bix_input::eListenMode::Pass ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_2( 1, r2bix_input::eListenMode::Pass ) );
				DECL_MAIN( r2bix_input::Listener4Keyboard l_3( 3, r2bix_input::eListenMode::Pass ) );

				LF();

				PROC_MAIN( m.AddListener( &l_1 ) );
				PROC_MAIN( m.AddListener( &l_2 ) );
				PROC_MAIN( m.AddListener( &l_3 ) );

				LF();

				EXPECT_EQ( ( *m.GetListenerContainer4Keyboard().begin() ), &l_3 );
				EXPECT_EQ( ( *( ++m.GetListenerContainer4Keyboard().begin() ) ), &l_1);
				EXPECT_EQ( ( *( ++++m.GetListenerContainer4Keyboard().begin() ) ), &l_2);

				LF();

				OUT_COMMENT( "Z ORder" );
				for( const auto l : m.GetListenerContainer4Keyboard() )
				{
					std::cout << l->GetOrder() << " ";
				}
				LF();
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InputManager_Order3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "InputManager : Order 3";
		};
	}
	r2tm::DoFunctionT InputManager_Order3::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUT_NOTE( "Listener 3개 추가" );
				OUT_NOTE( "각각 order 0, 1, 2" );
				OUT_NOTE( "1번 Listener의 eListenMode 는 Block" );

				LF();

				OUT_NOTE( "숫자 1 키를 누르면 Listener가 2, 1 순으로 작동하고 0번은 무시 되어야 한다." );
			}

			LS();

			{
				OUT_STRING( "[ESC] Exit" );
				OUT_STRING( "[1] Check" );
			}

			LS();

			r2bix_input::InputManager input_manager( 0, 0 );

			r2bix_input::Listener4Keyboard l_0( 0, r2bix_input::eListenMode::Pass );
			l_0.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_1, []( r2bix_input::eKeyStep s )->bool
			{
				std::cout << "Order 0 : " << ( int )s << r2tm::linefeed;
				return false;
			} );
			input_manager.AddListener( &l_0 );

			r2bix_input::Listener4Keyboard l_1( 1, r2bix_input::eListenMode::Block );
			l_1.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_1, []( r2bix_input::eKeyStep s )->bool
			{
				std::cout << "\t\t\t" << "Order 1 : " << ( int )s << r2tm::linefeed;
				return true;
			} );
			input_manager.AddListener( &l_1 );

			r2bix_input::Listener4Keyboard l_2( 2, r2bix_input::eListenMode::Pass );
			l_2.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_1, []( r2bix_input::eKeyStep s )->bool
			{
				std::cout << "\t\t\t\t\t\t" << "Order 2 : " << ( int )s << r2tm::linefeed;
				return false;
			} );
			input_manager.AddListener( &l_2 );

			{
				do
				{

					input_manager.Update();

				} while( !input_manager.HasInput( r2bix_input::eKeyCode::VK_ESCAPE ) );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}