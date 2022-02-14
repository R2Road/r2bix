#include "pch.h"
#include "console_screen_buffer_manager_test.h"

#include "base/r2base_eTestEndAction.h"

#include "game/r2game_ScreenBufferManager.h"

namespace console_screen_buffer_manager_test
{
	r2base::iTest::TitleFunc MakeSecondBuffer::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Manager : Make Second Buffer";
		};
	}
	r2base::iTest::DoFunc MakeSecondBuffer::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2game::ScreenBufferManager screen_buffer_manager;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2game::ScreenBufferManager screen_buffer_manager;" << r2::linefeed;
			}

			std::cout << r2::split;

			{
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}