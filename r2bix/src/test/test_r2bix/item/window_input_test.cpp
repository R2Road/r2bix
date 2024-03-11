#include "window_input_test.h"

#include <algorithm>

#include "r2bix_input_InputManager.h"
#include "r2bix_input_MachineInputCollector.h"
#include "r2bix_input_KeyboardInputListener.h"

#include "r2_RectInt.h"
#include "r2_FPSTimer.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

namespace window_input_test
{
	r2tm::TitleFunctionT TestKeyboardInputCollector_Keyboard::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Keyboard Input Collector : Keyboard";
			};
	}
	r2tm::DoFunctionT TestKeyboardInputCollector_Keyboard::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				std::cout << "[ESC] Exit" << r2tm::linefeed;
				std::cout << "[WASD] Move" << r2tm::linefeed;

				r2bix_input::MachineInputCollector keyboard_input_collector;
				r2bix_input::ObservationKeys observation_keys( {
					0x1B		// esc
					, 0x41		// a
					, 0x44		// d
					, 0x53		// s
					, 0x57		// w
					} );

				keyboard_input_collector.AddObservationKeys( observation_keys );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2tm::WindowUtility::CursorPoint pos{ 20, 20 };
					r2tm::WindowUtility::CursorPoint temp_pos{ 20, 20 };

					r2tm::WindowUtility::MoveCursorPoint( pos );
					std::cout << '@';

					while( 1 )
					{
						keyboard_input_collector.Collect();

						//
						// ESC
						//
						if( keyboard_input_collector.HasInput( 0x1B ) )
						{
							break;
						}

						if( fps_timer.Update() )
						{
							temp_pos = pos;

							if( keyboard_input_collector.HasInput( 0x41 ) )
							{
								--temp_pos.x;
							}
							if( keyboard_input_collector.HasInput( 0x44 ) )
							{
								++temp_pos.x;
							}
							if( keyboard_input_collector.HasInput( 0x57 ) )
							{
								--temp_pos.y;
							}
							if( keyboard_input_collector.HasInput( 0x53 ) )
							{
								++temp_pos.y;
							}
							if( !stage_area.IsIn( temp_pos.x, temp_pos.y ) )
							{
								temp_pos.x = std::clamp( temp_pos.x, static_cast< short >( stage_area.GetMinX() ), static_cast< short >( stage_area.GetMaxX() ) );
								temp_pos.y = std::clamp( temp_pos.y, static_cast< short >( stage_area.GetMinY() ), static_cast< short >( stage_area.GetMaxY() ) );
							}

							if( temp_pos.x != pos.x || temp_pos.y != pos.y )
							{
								r2tm::WindowUtility::MoveCursorPoint( pos );
								std::cout << ' ';
								r2tm::WindowUtility::MoveCursorPoint( temp_pos );
								std::cout << '@';

								pos = temp_pos;
							}
						}
					}
				}

				return r2tm::eDoLeaveAction::Pause;
			};
	}



	r2tm::TitleFunctionT TestKeyboardInputCollector_Mouse::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Keyboard Input Collector : Mouse";
			};
	}
	r2tm::DoFunctionT TestKeyboardInputCollector_Mouse::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				std::cout << "[ ESC ] Exit" << r2tm::linefeed;
				std::cout << "[MOUSE] Move" << r2tm::linefeed;

				r2bix_input::MachineInputCollector keyboard_input_collector;
				r2bix_input::ObservationKeys observation_keys( { 0x1B } ); // ESC
				keyboard_input_collector.AddObservationKeys( observation_keys );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2bix_input::CursorPoint pos;
					r2bix_input::CursorPoint temp_pos;

					r2tm::WindowUtility::MoveCursorPoint( pos.GetX(), pos.GetY() );
					std::cout << '@';

					while( 1 )
					{
						keyboard_input_collector.Collect();

						//
						// ESC
						//
						if( keyboard_input_collector.HasInput( 0x1B ) )
						{
							break;
						}

						if( fps_timer.Update() )
						{
							temp_pos = keyboard_input_collector.GetCursorPoint();

							if( !stage_area.IsIn( temp_pos ) )
							{
								temp_pos = stage_area.Clamp( temp_pos );
							}

							if( temp_pos != pos )
							{
								r2tm::WindowUtility::MoveCursorPoint( pos.GetX(), pos.GetY() );
								std::cout << ' ';
								r2tm::WindowUtility::MoveCursorPoint( temp_pos.GetX(), temp_pos.GetY() );
								std::cout << '@';

								pos = temp_pos;
							}
						}

						r2tm::WindowUtility::MoveCursorPoint( 0, 8 );
						std::cout << "      ";
						r2tm::WindowUtility::MoveCursorPoint( 0, 8 );
						std::cout << keyboard_input_collector.GetCursorPoint().GetX() << " " << keyboard_input_collector.GetCursorPoint().GetY();
					}
				}

				return r2tm::eDoLeaveAction::Pause;
			};
	}



	r2tm::TitleFunctionT KeyStatus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Window Input : KeyStatus";
		};
	}
	r2tm::DoFunctionT KeyStatus::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[A] ..." << r2tm::linefeed;

			r2bix_input::InputManager input_manager;
			r2bix_input::KeyboardInputListener keyboard_input_listener( {
				0x1B		// esc
				, 0x41		// a
			} );

			input_manager.AddInputListener( &keyboard_input_listener );

			LS();

			{
				auto last_input_status = keyboard_input_listener.Get( 1 );
				while( 1 )
				{
					input_manager.Update();

					//
					// ESC
					//
					if( keyboard_input_listener.IsPushed( 0 ) )
					{
						break;
					}

					//
					// A
					//
					if( last_input_status != keyboard_input_listener.Get( 1 ) )
					{
						last_input_status = keyboard_input_listener.Get( 1 );
						std::cout << "status : " << static_cast<int>( last_input_status ) << r2tm::linefeed;
					}
				}
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}


	
	r2tm::TitleFunctionT TestKeyboardInputListener::GetTitleFunction() const
	{
		return []()->const char*
			{
				return "Keyboard Input Listener";
			};
	}
	r2tm::DoFunctionT TestKeyboardInputListener::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
			{
				LS();

				std::cout << "[ESC] Exit" << r2tm::linefeed;
				std::cout << "[WASD] Move" << r2tm::linefeed;

				r2bix_input::InputManager input_manager;
				r2bix_input::KeyboardInputListener keyboard_input_listener( {
					0x1B		// esc
					, 0x41		// a
					, 0x44		// d
					, 0x53		// s
					, 0x57		// w
					} );

				input_manager.AddInputListener( &keyboard_input_listener );

				LS();

				{
					r2::FPSTimer fps_timer( 60u );
					r2::RectInt stage_area( 6, 10, 50, 30 );
					r2tm::WindowUtility::CursorPoint pos{ 20, 20 };
					r2tm::WindowUtility::CursorPoint temp_pos{ 20, 20 };

					r2tm::WindowUtility::MoveCursorPoint( pos );
					std::cout << '@';

					while( 1 )
					{
						input_manager.Update();

						//
						// ESC
						//
						if( keyboard_input_listener.IsPushed( 0 ) )
						{
							break;
						}

						if( fps_timer.Update() )
						{
							temp_pos = pos;

							if( keyboard_input_listener.HasInput( 1 ) )
							{
								--temp_pos.x;
							}
							if( keyboard_input_listener.HasInput( 2 ) )
							{
								++temp_pos.x;
							}
							if( keyboard_input_listener.HasInput( 4 ) )
							{
								--temp_pos.y;
							}
							if( keyboard_input_listener.HasInput( 3 ) )
							{
								++temp_pos.y;
							}
							if( !stage_area.IsIn( temp_pos.x, temp_pos.y ) )
							{
								temp_pos.x = std::clamp( temp_pos.x, static_cast< short >( stage_area.GetMinX() ), static_cast< short >( stage_area.GetMaxX() ) );
								temp_pos.y = std::clamp( temp_pos.y, static_cast< short >( stage_area.GetMinY() ), static_cast< short >( stage_area.GetMaxY() ) );
							}

							if( temp_pos.x != pos.x || temp_pos.y != pos.y )
							{
								r2tm::WindowUtility::MoveCursorPoint( pos );
								std::cout << ' ';
								r2tm::WindowUtility::MoveCursorPoint( temp_pos );
								std::cout << '@';

								pos = temp_pos;
							}
						}
					}
				}

				return r2tm::eDoLeaveAction::Pause;
			};
	}
}