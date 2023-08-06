#include "key_code_viewer.h"

#include <conio.h>

#include "r2cm/r2cm_ostream.h"

namespace key_code_viewer
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key Code Viewer";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			std::cout << "[ESC] End" << r2cm::linefeed;

			std::cout << r2cm::split;

			bool process = true;
			int input = 0;
			do
			{
				input = _getch();

				std::cout << "Key : " << input << r2cm::linefeed;

				process = ( 27 != input ); // ESC
			} while( process );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}