#include "pch.h"
#include "window_input_test.h"

#include <windows.h>

#include "base/r2_eTestResult.h"

#include "input/r2_KeyboardInputCollector.h"

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

			r2::KeyboardInputCollector keyboard_input_collector;

			std::cout << r2::split;

			{
				while( 1 )
				{
					keyboard_input_collector.Collect();

					//
					// ESC
					//
					if( keyboard_input_collector.IsPressed( VK_ESCAPE ) )
					{
						break;
					}
				}
			}

			return r2::eTestResult::RunTest;
		};
	}
}