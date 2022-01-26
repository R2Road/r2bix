#include "pch.h"
#include "window_input_test.h"

#include <assert.h>
#include <conio.h> // _kbhit(), _getch()
#include <windows.h>

#include "base/r2_eTestResult.h"

namespace window_input_test
{
	void ShowCurrentConsoleMode()
	{
		DWORD temp_console_mode;

		GetConsoleMode( GetStdHandle( STD_INPUT_HANDLE ), &temp_console_mode );
		std::cout << r2::tab << "Current Console Mode : " << temp_console_mode << r2::linefeed;
	}

	r2::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Window Input : Basic";
		};
	}
	r2::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;

			std::cout << r2::split;

			HANDLE hStdInputHandle = GetStdHandle( STD_INPUT_HANDLE );
			DWORD last_console_mode;

			std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
			std::cout << r2::tab2 << "HANDLE hStdInputHandle = GetStdHandle( STD_INPUT_HANDLE );" << r2::linefeed;
			std::cout << r2::tab2 << "DWORD last_console_mode;" << r2::linefeed;

			std::cout << r2::split;

			{
				if( !GetConsoleMode( hStdInputHandle, &last_console_mode ) )
				{
					assert( false && "GetConsoleMode( hStdInputHandle, &last_console_mode )" );
				}

				std::cout << r2::tab << "+ Backup Console Mode" << r2::linefeed2;
				std::cout << r2::tab2 << "GetConsoleMode( hStdInputHandle, &last_console_mode )" << r2::linefeed2;

				std::cout << r2::linefeed;
				ShowCurrentConsoleMode();
			}

			std::cout << r2::split;

			{
				const DWORD new_console_mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
				if( !SetConsoleMode( hStdInputHandle, new_console_mode ) )
				{
					assert( false && "SetConsoleMode( hStdInputHandle, new_console_mode )" );
				}

				std::cout << r2::tab << "+ Change Console Mode" << r2::linefeed2;
				std::cout << r2::tab2 << "const DWORD new_console_mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;" << r2::linefeed;
				std::cout << r2::tab2 << "SetConsoleMode( hStdInputHandle, new_console_mode )" << r2::linefeed;
				std::cout << r2::tab3 << "> " << new_console_mode << r2::linefeed;

				std::cout << r2::linefeed;
				ShowCurrentConsoleMode();
			}

			std::cout << r2::split;

			{
				//
				// # REF
				// https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events?redirectedfrom=MSDN
				//

				INPUT_RECORD input_records[128];
				DWORD current_record_count;
				bool process = true;

				do
				{
					if( !ReadConsoleInput(
						hStdInputHandle				// input buffer handle
						, input_records				// buffer to read into
						, 128						// size of read buffer
						, &current_record_count		// number of records read
					) )
					{
						assert( false && "ReadConsoleInput" );
					}

					for( DWORD i = 0; current_record_count > i; ++i )
					{
						if( KEY_EVENT == input_records[i].EventType )
						{
							std::cout << "================== KEY_EVENT ==================" << r2::linefeed;
							std::cout << "EventType : " << input_records[i].EventType << r2::linefeed;
							std::cout << "Event.KeyEvent.uChar.AsciiChar : " << input_records[i].Event.KeyEvent.uChar.AsciiChar << r2::linefeed;
							std::cout << "Event.KeyEvent.bKeyDown : " << input_records[i].Event.KeyEvent.bKeyDown << r2::linefeed;
							std::cout << "Event.KeyEvent.wVirtualKeyCode : " << input_records[i].Event.KeyEvent.wVirtualKeyCode << r2::linefeed;
							std::cout << "===============================================" << r2::linefeed;

							if( 27 == input_records[i].Event.KeyEvent.wVirtualKeyCode )
							{
								process = false;
							}
						}
					}
				} while( process );
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "Press Any Key : Rollback" << r2::linefeed;
				_getch();

				//
				// Rollback
				//
				SetConsoleMode( hStdInputHandle, last_console_mode );

				std::cout << r2::linefeed;
				ShowCurrentConsoleMode();
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}