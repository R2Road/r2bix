#include "pch.h"
#include "window_input_test.h"

#include <algorithm>
#include <windows.h>

#include "base/r2_eTestResult.h"

#include "input/r2_input_KeyboardInputCollector.h"
#include "input/r2_input_KeyboardInputListener.h"

#include "r2/r2_RectInt.h"
#include "renderer/r2_FPSTimer.h"

namespace window_input_test
{
	r2::iTest::TitleFunc TestKeyboardInputCollector::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Input Collector";
		};
	}
	r2::iTest::DoFunc TestKeyboardInputCollector::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
			std::cout << "[ESC] Exit" << r2::linefeed;
			std::cout << "[WASD] Move" << r2::linefeed;

			r2_input::KeyboardInputCollector keyboard_input_collector;
			r2_input::KeyboardInputListener keyboard_input_listener;

			keyboard_input_collector.AddListener( &keyboard_input_listener );

			std::cout << r2::split;

			{
				r2::FPSTimer fps_timer( 60u );
				r2::RectInt stage_area( 6, 10, 50, 30 );
				COORD pos = { 20, 20 };

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
						SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
						std::cout << ' ';

						if( keyboard_input_listener.HasInput( 1 ) )
						{
							--pos.X;
						}
						if( keyboard_input_listener.HasInput( 2 ) )
						{
							++pos.X;
						}
						if( keyboard_input_listener.HasInput( 4 ) )
						{
							--pos.Y;
						}
						if( keyboard_input_listener.HasInput( 3 ) )
						{
							++pos.Y;
						}
						if( !stage_area.ContainsPoint( pos.X, pos.Y ) )
						{
							pos.X = std::clamp( pos.X, static_cast<short>( stage_area.GetMinX() ), static_cast<short>( stage_area.GetMaxX() ) );
							pos.Y = std::clamp( pos.Y, static_cast<short>( stage_area.GetMinY() ), static_cast<short>( stage_area.GetMaxY() ) );
						}

						SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
						std::cout << '@';
					}
				}
			}

			return r2::eTestResult::RunTest;
		};
	}
}