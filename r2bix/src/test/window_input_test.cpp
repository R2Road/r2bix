#include "pch.h"
#include "window_input_test.h"

#include <windows.h>

#include "base/r2_eTestResult.h"

#include "input/r2_input_KeyboardInputCollector.h"
#include "input/r2_input_KeyboardInputListener.h"

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
				COORD pos = { 10, 11 };

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

					SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
					std::cout << ' ';

					if( keyboard_input_listener.IsPushed( 1 ) )
					{
						--pos.X;
					}
					if( keyboard_input_listener.IsPushed( 2 ) )
					{
						++pos.X;
					}
					if( keyboard_input_listener.IsPushed( 4 ) )
					{
						--pos.Y;
					}
					if( keyboard_input_listener.IsPushed( 3 ) )
					{
						++pos.Y;
					}

					SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
					std::cout << '@';
				}
			}

			return r2::eTestResult::RunTest;
		};
	}
}