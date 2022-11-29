#include "console_screen_buffer_test.h"

#include <Windows.h>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

namespace console_screen_buffer_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Info";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE ) );
			DECLARATION_MAIN( CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info );

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto result = GetConsoleScreenBufferInfo( hStdout, &cs_buffer_info ) );
			EXPECT_TRUE( result );

			std::cout << r2cm::split;

			if( result )
			{
				std::cout << r2cm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwCursorPosition" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "X : " << cs_buffer_info.dwCursorPosition.X << r2cm::linefeed;
				std::cout << r2cm::tab2 << "Y : " << cs_buffer_info.dwCursorPosition.Y << r2cm::linefeed2;

				std::cout << r2cm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwMaximumWindowSize" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "X : " << cs_buffer_info.dwMaximumWindowSize.X << r2cm::linefeed;
				std::cout << r2cm::tab2 << "Y : " << cs_buffer_info.dwMaximumWindowSize.Y << r2cm::linefeed2;

				std::cout << r2cm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwSize" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "X : " << cs_buffer_info.dwSize.X << r2cm::linefeed;
				std::cout << r2cm::tab2 << "Y : " << cs_buffer_info.dwSize.Y << r2cm::linefeed2;

				std::cout << r2cm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.srWindow" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "Left : " << cs_buffer_info.srWindow.Left << r2cm::linefeed;
				std::cout << r2cm::tab2 << "Top : " << cs_buffer_info.srWindow.Top << r2cm::linefeed;
				std::cout << r2cm::tab2 << "Right : " << cs_buffer_info.srWindow.Right << r2cm::linefeed2;
				std::cout << r2cm::tab2 << "Bottom : " << cs_buffer_info.srWindow.Bottom << r2cm::linefeed;

				std::cout << r2cm::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.wAttributes" << r2cm::linefeed;
				std::cout << r2cm::tab2 << cs_buffer_info.wAttributes << r2cm::linefeed;
			}
			else
			{
				std::cout << r2cm::tab << "Failed : " "GetConsoleScreenBufferInfo( hStdout, &cs_buffer_info )" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}