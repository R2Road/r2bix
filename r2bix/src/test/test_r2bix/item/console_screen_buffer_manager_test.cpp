#include "console_screen_buffer_manager_test.h"

#include <conio.h>

#include "r2bix/r2base_ScreenBufferManager.h"
#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_constant.h"

namespace console_screen_buffer_manager_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Manager : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2base::ScreenBufferManager screen_buffer_manager );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "[ESC] End" << r2cm::linefeed;
				std::cout << r2cm::tab << "[Any Key] screen_buffer_manager.Swap();" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

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

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}