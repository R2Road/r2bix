#include "console_screen_buffer_manager_test.h"

#include <conio.h>

#include "r2bix_director_ScreenBufferManager.h"
#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace console_screen_buffer_manager_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Manager : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_director::ScreenBufferManager screen_buffer_manager );

			LS();

			{
				std::cout << r2tm::tab << "[ESC] End" << r2tm::linefeed;
				std::cout << r2tm::tab << "[Any Key] screen_buffer_manager.Swap();" << r2tm::linefeed;
			}

			LS();

			{
				int key_code = -1;
				do
				{
					screen_buffer_manager.Swap();

					if( _kbhit() )
					{
						key_code = _getch();
					}

				} while( 27 != key_code );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}