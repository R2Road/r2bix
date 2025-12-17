#include "test_input___listener_4_keyboard.hpp"

#include "r2_rect_int.hpp"
#include "r2_fps_timer.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"
#include "r2tm/r2tm_windows_utility.hpp"

#include "r2bix_input_InputManager.h"
#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

namespace test_input___listener_4_keyboard
{
	r2tm::TitleFunctionT KeyStatus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Listener : KeyStatus";
		};
	}
	r2tm::DoFunctionT KeyStatus::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[A] ..." << r2tm::linefeed;

			r2bix_input::InputManager input_manager( 0, 0 );

			bool bPlay = true;
			r2bix_input::Listener4Keyboard keyboard_listener;
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStep )->bool
			{
				bPlay = false;
				return false;
			} );

			bool bAChanged = false;
			r2bix_input::eKeyStep as = r2bix_input::eKeyStep::None;
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_A, [&bAChanged, &as]( r2bix_input::eKeyStep s )->bool
			{
				bAChanged = true;
				as = s;
				return false;
			} );

			input_manager.AddListener( &keyboard_listener );

			LS();

			{
				long long frame = 0ll;
				do
				{

					input_manager.Update();

					//
					// A
					//
					if( bAChanged )
					{
						bAChanged = false;
						std::cout << "status : " << static_cast< int >( as ) << "    " << frame << r2tm::linefeed;
					}

					++frame;

				} while( bPlay );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Play::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Listener : Play";
		};
	}
	r2tm::DoFunctionT Play::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[WASD] Move" << r2tm::linefeed;

			r2bix_input::InputManager input_manager( 0, 0 );

			bool bPlay = true;
			r2bix_input::Listener4Keyboard keyboard_listener;
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStep )->bool
			{
				bPlay = false;
				return false;
			} );

			r2tm::WindowsUtility::CursorPoint new_pos{ 20, 20 };
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_A, [&new_pos]( r2bix_input::eKeyStep )->bool
			{
				--new_pos.x;
				return false;
			} );
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_D, [&new_pos]( r2bix_input::eKeyStep )->bool
			{
				++new_pos.x;
				return false;
			} );
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_S, [&new_pos]( r2bix_input::eKeyStep )->bool
			{
				++new_pos.y;
				return false;
			} );
			keyboard_listener.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_W, [&new_pos]( r2bix_input::eKeyStep )->bool
			{
				--new_pos.y;
				return false;
			} );

			input_manager.AddListener( &keyboard_listener );

			LS();

			{
				r2::FPSTimer fps_timer( 60u );
				r2::RectInt stage_area( 6, 10, 50, 30 );

				r2tm::WindowsUtility::CursorPoint pos{ 20, 20 };
				r2tm::WindowsUtility::MoveCursorPoint( pos );
				std::cout << '@';

				do
				{

					if( fps_timer.Update() )
					{
						input_manager.Update();

						if( !stage_area.IsIn( new_pos.x, new_pos.y ) )
						{
							new_pos.x = std::clamp( new_pos.x, static_cast< short >( stage_area.GetMinX() ), static_cast< short >( stage_area.GetMaxX() ) );
							new_pos.y = std::clamp( new_pos.y, static_cast< short >( stage_area.GetMinY() ), static_cast< short >( stage_area.GetMaxY() ) );
						}

						if( new_pos.x != pos.x || new_pos.y != pos.y )
						{
							r2tm::WindowsUtility::MoveCursorPoint( pos );
							std::cout << ' ';
							r2tm::WindowsUtility::MoveCursorPoint( new_pos );
							std::cout << '@';

							pos = new_pos;
						}
					}

				} while( bPlay );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Order::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Listener : Order";
		};
	}
	r2tm::DoFunctionT Order::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[1] Check" << r2tm::linefeed;

			bool bPlay = true;
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
			l_2.SetCallback4KeyStepChanged( r2bix_input::eKeyCode::VK_ESCAPE, [&bPlay]( r2bix_input::eKeyStep )->bool
			{
				bPlay = false;
				return false;
			} );
			input_manager.AddListener( &l_2 );


			LS();

			{
				do
				{

					input_manager.Update();

				} while( bPlay );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}