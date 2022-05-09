#include "pch.h"
#include "console_screen_buffer_test.h"

#include <Windows.h>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_constant.h"

namespace console_screen_buffer_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Info";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed2;

			std::cout << r2::split;

			DECLARATION_MAIN( HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE ) );
			DECLARATION_MAIN( CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info );

			std::cout << r2::split;

			DECLARATION_MAIN( const auto result = GetConsoleScreenBufferInfo( hStdout, &cs_buffer_info ) );
			EXPECT_TRUE( result );

			std::cout << r2::split;

			if( result )
			{
				std::cout << r2::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwCursorPosition" << r2::linefeed;
				std::cout << r2::tab2 << "X : " << cs_buffer_info.dwCursorPosition.X << r2::linefeed;
				std::cout << r2::tab2 << "Y : " << cs_buffer_info.dwCursorPosition.Y << r2::linefeed2;

				std::cout << r2::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwMaximumWindowSize" << r2::linefeed;
				std::cout << r2::tab2 << "X : " << cs_buffer_info.dwMaximumWindowSize.X << r2::linefeed;
				std::cout << r2::tab2 << "Y : " << cs_buffer_info.dwMaximumWindowSize.Y << r2::linefeed2;

				std::cout << r2::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.dwSize" << r2::linefeed;
				std::cout << r2::tab2 << "X : " << cs_buffer_info.dwSize.X << r2::linefeed;
				std::cout << r2::tab2 << "Y : " << cs_buffer_info.dwSize.Y << r2::linefeed2;

				std::cout << r2::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.srWindow" << r2::linefeed;
				std::cout << r2::tab2 << "Left : " << cs_buffer_info.srWindow.Left << r2::linefeed;
				std::cout << r2::tab2 << "Top : " << cs_buffer_info.srWindow.Top << r2::linefeed;
				std::cout << r2::tab2 << "Right : " << cs_buffer_info.srWindow.Right << r2::linefeed2;
				std::cout << r2::tab2 << "Bottom : " << cs_buffer_info.srWindow.Bottom << r2::linefeed;

				std::cout << r2::tab << "+ CONSOLE_SCREEN_BUFFER_INFO.wAttributes" << r2::linefeed;
				std::cout << r2::tab2 << cs_buffer_info.wAttributes << r2::linefeed;
			}
			else
			{
				std::cout << r2::tab << "Failed : " "GetConsoleScreenBufferInfo( hStdout, &cs_buffer_info )" << r2::linefeed;
			}

			std::cout << r2::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}