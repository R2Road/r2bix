#include "pch.h"
#include "window_input_test.h"

#include <windows.h>

#include "base/r2_eTestResult.h"

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
			std::cout << "[SPACE] Do" << r2::linefeed;

			std::cout << r2::split;

			std::cout << r2::tab << "+ Key Info : VK_SPACE" << r2::linefeed << r2::linefeed3;

			std::cout << r2::split;

			{
				int key_value = 0;

				while( 1 )
				{
					//
					// Process
					//
					key_value = GetAsyncKeyState( VK_SPACE );

					//
					// View
					//
					SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 9 } );
					printf_s(
						"\t\t" "Key State : %c \n"
						"\t\t" "Key Value : hex : %8x \n"
						, ( key_value & 0x8000 ? 'O' : 'X' )
						, key_value
					);

					//
					// ESC
					//
					if( GetKeyState( VK_ESCAPE ) & 0x8000 )
					{
						break;
					}
				}
			}

			return r2::eTestResult::RunTest;
		};
	}
}