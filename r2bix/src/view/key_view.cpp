#include "key_view.h"

#include <conio.h>

#include "r2tm/r2tm_ostream.h"

namespace key_code_viewer
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key View";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			std::cout << "[ESC] End" << r2tm::linefeed;

			LS();

			bool process = true;
			int input = 0;
			do
			{
				input = _getch();

				std::cout << "Key : " << input << r2tm::linefeed;

				process = ( 27 != input ); // ESC
			} while( process );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}