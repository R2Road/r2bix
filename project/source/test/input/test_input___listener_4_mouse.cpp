#include "test_input___listener_4_mouse.hpp"

#include <algorithm>

#include "r2_rect_int.hpp"
#include "r2_fps_timer.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "r2bix_input_Listener4Mouse.hpp"
#include "r2bix_input_InputManager.hpp"


namespace test_input___listener_4_mouse
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mouse Listener : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUT_SUBJECT( "기본 생성자" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Mouse l );

				LF();

				EXPECT_EQ( 0, l.GetOrder() );
				EXPECT_TRUE( r2bix_input::eListenMode::Pass == l.GetListenMode() );
				EXPECT_TRUE( l.IsActivated() );
				EXPECT_TRUE( l.GetObservationKeyList().Empty() );
			}

			LS();

			{
				OUT_SUBJECT( "Order와 ListenMode를 인자로 받는 생성자" );

				LF();

				DECL_MAIN( r2bix_input::Listener4Mouse l( 3, r2bix_input::eListenMode::Block ) );

				LF();

				EXPECT_EQ( 3, l.GetOrder() );
				EXPECT_TRUE( r2bix_input::eListenMode::Block == l.GetListenMode() );
				EXPECT_TRUE( l.IsActivated() );
				EXPECT_TRUE( l.GetObservationKeyList().Empty() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Size_Binary::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mouse Listener : Size / Binary";
		};
	}
	r2tm::DoFunctionT Size_Binary::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECL_MAIN( r2bix_input::Listener4Mouse l( 3, r2bix_input::eListenMode::Block ) );

				LF();

				OUT_SIZE( l );

				LF();

				OUT_BINARY( l );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT KeyStatus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mouse Listener : KeyStatus";
		};
	}
	r2tm::DoFunctionT KeyStatus::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[  ESC  ] Exit" << r2tm::linefeed;
			std::cout << "[L Click] ..." << r2tm::linefeed;
			std::cout << "[M Click] ..." << r2tm::linefeed;
			std::cout << "[R Click] ..." << r2tm::linefeed;

			r2bix_input::InputManager manager( 0, 0 );

			r2bix_input::Listener4Mouse mouse_listener;
			mouse_listener.SetCallback4KeyStepChanged(
				  r2bix_input::eKeyCode::VK_LBUTTON
				, []( const r2bix_input::eKeyStep s )->bool
				{
					std::cout << "L : " << static_cast<int>( s ) << r2tm::linefeed;
					return false;
				}
			);
			mouse_listener.SetCallback4KeyStepChanged(
				  r2bix_input::eKeyCode::VK_MBUTTON
				, []( const r2bix_input::eKeyStep s )->bool
				{
					std::cout << "\t\t\t" << "M : " << static_cast<int>( s ) << r2tm::linefeed;
					return false;
				}
			);
			mouse_listener.SetCallback4KeyStepChanged(
				  r2bix_input::eKeyCode::VK_RBUTTON
				, []( const r2bix_input::eKeyStep s )->bool
				{
					std::cout << "\t\t\t\t\t\t" << "R : " << static_cast<int>( s ) << r2tm::linefeed;
					return false;
				}
			);

			manager.AddListener( &mouse_listener );

			LS();

			{
				do
				{
					manager.Update();
					
				} while( !manager.mKeyStatusProcessor.HasInput( r2bix_input::eKeyCode::VK_ESCAPE ) );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Cursor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Mouse Listener : Cursor";
		};
	}
	r2tm::DoFunctionT Cursor::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ ESC  ] Exit" << r2tm::linefeed;
			std::cout << "[Cursor] ..." << r2tm::linefeed;

			r2bix_input::InputManager manager( 0, 0 );

			r2bix_input::CursorPoint c;
			bool bMoved = false;
			r2bix_input::Listener4Mouse mouse_listener;
			mouse_listener.SetCallback4CursorMoved( [&c, &bMoved]( const r2bix_input::CursorPoint cursor_point )->bool{

				c = cursor_point;
				bMoved = true;

				return true;
			} );

			manager.AddListener( &mouse_listener );

			LS();

			{
				do
				{
					manager.Update();

					//
					// Cursor Move
					//
					if( bMoved )
					{
						bMoved = false;

						r2tm::WindowsUtility::MoveCursorPoint( 0, 10 );
						std::cout << "                                     ";

						r2tm::WindowsUtility::MoveCursorPoint( 0, 10 );
						std::cout
							<< "X : "
							<< static_cast< int >( c.GetX() )
							<< "\tY : "
							<< static_cast< int >( c.GetY() )
							<< "         "
							<< r2tm::linefeed;
					}
				} while( !manager.mKeyStatusProcessor.HasInput( r2bix_input::eKeyCode::VK_ESCAPE ) );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}