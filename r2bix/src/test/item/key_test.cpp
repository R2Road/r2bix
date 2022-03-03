#include "pch.h"
#include "key_test.h"

#include <conio.h>

#include "test/r2test_eTestEndAction.h"

namespace key_test
{
	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Key : Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed2;
			std::cout << "[ESC] End" << r2::linefeed;

			std::cout << r2::split;

			bool process = true;
			int input = 0;
			do
			{
				input = _getch();

				std::cout << "Key : " << input << r2::linefeed;

				process = ( 27 != input ); // ESC
			} while( process );

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}