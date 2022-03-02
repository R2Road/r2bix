#include "pch.h"
#include "console_screen_buffer_manager_test.h"

#include <conio.h>

#include "base/r2base_eTestEndAction.h"

#include "game/r2game_ScreenBufferManager.h"

namespace console_screen_buffer_manager_test
{
	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Manager : Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			r2game::ScreenBufferManager screen_buffer_manager;

			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2node::ScreenBufferManager screen_buffer_manager;" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "[ESC] End" << r2::linefeed;
				std::cout << r2::tab << "[Any Key] screen_buffer_manager.Swap();" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				int key_code = -1;
				do
				{
					key_code = _getch();
					if( 27 == key_code )
					{
						break;
					}

					screen_buffer_manager.Swap();

				} while( true );
			}

			return r2base::eTestEndAction::Pause;
		};
	}
}