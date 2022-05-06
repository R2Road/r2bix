#include "pch.h"
#include "miniaudio_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
// # Miniaudio REF : https://miniaud.io/docs/manual/index.html

namespace miniaudio_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( ma_result result );
			DECLARATION_MAIN( ma_engine engine );

			std::cout << r2::split;

			{
				PROCESS_MAIN( result = ma_engine_init( NULL, &engine ) );
				EXPECT_EQ( MA_SUCCESS, result );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( ma_engine_uninit( &engine ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}