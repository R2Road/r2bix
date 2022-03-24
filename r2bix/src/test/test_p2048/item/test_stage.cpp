#include "pch.h"
#include "test_stage.h"

#include <conio.h>
#include <Windows.h>

#include "base/r2base_Director.h"
#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "p2048/p2048_Stage.h"

namespace test_stage
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 10, 10 ) );

			std::cout << r2::split;

			{
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}