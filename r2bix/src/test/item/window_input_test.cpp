#include "pch.h"
#include "window_input_test.h"

#include <algorithm>
#include <windows.h>

#include "test/r2test_eTestEndAction.h"

#include "input/r2input_KeyboardInputCollector.h"
#include "input/r2input_KeyboardInputListener.h"

#include "r2/r2_RectInt.h"
#include "base/r2base_FPSTimer.h"

namespace window_input_test
{
	r2test::iTest_Deprecated::TitleFunc TestKeyboardInputCollector::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Input Collector";
		};
	}
	r2test::iTest_Deprecated::DoFunc TestKeyboardInputCollector::GetDoFunction()
	{
		return []( r2base::Director& )->r2test::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
			std::cout << "[ESC] Exit" << r2::linefeed;
			std::cout << "[WASD] Move" << r2::linefeed;

			r2input::KeyboardInputCollector keyboard_input_collector;
			r2input::KeyboardInputListener keyboard_input_listener( {
				0x1B		// esc
				, 0x41		// a
				, 0x44		// d
				, 0x53		// s
				, 0x57		// w
			} );

			keyboard_input_collector.AddListener( &keyboard_input_listener );

			std::cout << r2::split;

			{
				r2base::FPSTimer fps_timer( 60u );
				r2::RectInt stage_area( 6, 10, 50, 30 );
				COORD pos = { 20, 20 };
				COORD temp_pos;

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
				std::cout << '@';

				while( 1 )
				{
					keyboard_input_collector.Collect();
					keyboard_input_listener.Update();

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
							--temp_pos.X;
						}
						if( keyboard_input_listener.HasInput( 2 ) )
						{
							++temp_pos.X;
						}
						if( keyboard_input_listener.HasInput( 4 ) )
						{
							--temp_pos.Y;
						}
						if( keyboard_input_listener.HasInput( 3 ) )
						{
							++temp_pos.Y;
						}
						if( !stage_area.ContainsPoint( temp_pos.X, temp_pos.Y ) )
						{
							temp_pos.X = std::clamp( temp_pos.X, static_cast<short>( stage_area.GetMinX() ), static_cast<short>( stage_area.GetMaxX() ) );
							temp_pos.Y = std::clamp( temp_pos.Y, static_cast<short>( stage_area.GetMinY() ), static_cast<short>( stage_area.GetMaxY() ) );
						}

						if( temp_pos.X != pos.X || temp_pos.Y != pos.Y )
						{
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
							std::cout << ' ';
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), temp_pos );
							std::cout << '@';

							pos = temp_pos;
						}
					}
				}
			}

			return r2test::eTestEndAction::Pause;
		};
	}
}