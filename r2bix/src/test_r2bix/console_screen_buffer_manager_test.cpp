#include "pch.h"
#include "console_screen_buffer_manager_test.h"

#include <conio.h>

#include "test/r2test_eTestEndAction.h"

#include "base/r2base_ScreenBufferManager.h"

namespace console_screen_buffer_manager_test
{
	r2test::iItem::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Manager : Basic";
		};
	}
	r2test::iItem::DoFunc Basic::GetDoFunction()
	{
		return []()->r2test::eTestEndAction
		{
			r2base::ScreenBufferManager screen_buffer_manager;

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

			return r2test::eTestEndAction::Pause;
		};
	}
}