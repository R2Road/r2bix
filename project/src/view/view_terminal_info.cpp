#include "view_terminal_info.h"

#include <Windows.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace view_terminal_info
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Terminal Info View";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE ) );
			DECLARATION_MAIN( CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info );

			LS();

			DECLARATION_MAIN( const auto result = GetConsoleScreenBufferInfo( hStdout, &cs_buffer_info ) );
			EXPECT_TRUE( result );

			LS();

			if( result )
			{
				std::cout << r2tm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwCursorPosition" << r2tm::linefeed;
				std::cout << r2tm::tab2 << "X : " << cs_buffer_info.dwCursorPosition.X << r2tm::linefeed;
				std::cout << r2tm::tab2 << "Y : " << cs_buffer_info.dwCursorPosition.Y << r2tm::linefeed2;

				std::cout << r2tm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwMaximumWindowSize" << r2tm::linefeed;
				std::cout << r2tm::tab2 << "X : " << cs_buffer_info.dwMaximumWindowSize.X << r2tm::linefeed;
				std::cout << r2tm::tab2 << "Y : " << cs_buffer_info.dwMaximumWindowSize.Y << r2tm::linefeed2;

				std::cout << r2tm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwSize" << r2tm::linefeed;
				std::cout << r2tm::tab2 << "X : " << cs_buffer_info.dwSize.X << r2tm::linefeed;
				std::cout << r2tm::tab2 << "Y : " << cs_buffer_info.dwSize.Y << r2tm::linefeed2;

				std::cout << r2tm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.srWindow" << r2tm::linefeed;
				std::cout << r2tm::tab2 << "Left : " << cs_buffer_info.srWindow.Left << r2tm::linefeed;
				std::cout << r2tm::tab2 << "Top : " << cs_buffer_info.srWindow.Top << r2tm::linefeed;
				std::cout << r2tm::tab2 << "Right : " << cs_buffer_info.srWindow.Right << r2tm::linefeed2;
				std::cout << r2tm::tab2 << "Bottom : " << cs_buffer_info.srWindow.Bottom << r2tm::linefeed;

				std::cout << r2tm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.wAttributes" << r2tm::linefeed;
				std::cout << r2tm::tab2 << cs_buffer_info.wAttributes << r2tm::linefeed;
			}
			else
			{
				std::cout << r2tm::tab << "Failed : " "GetConsoleScreenBufferInfo( hStdout, &cs_buffer_info )" << r2tm::linefeed;
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}