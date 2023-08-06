#include "key_code_viewer.h"

#include <conio.h>

#include "r2tm/r2tm_ostream.h"

namespace key_code_viewer
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key Code Viewer";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			std::cout << "[ESC] End" << r2tm::linefeed;

			std::cout << r2tm::split;

			bool process = true;
			int input = 0;
			do
			{
				input = _getch();

				std::cout << "Key : " << input << r2tm::linefeed;

				process = ( 27 != input ); // ESC
			} while( process );

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}