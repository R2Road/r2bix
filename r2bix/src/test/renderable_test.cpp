#include "pch.h"
#include "renderable_test.h"

#include "base/r2base_eTestEndAction.h"

namespace renderable_test
{
	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				//std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				//std::cout << r2::tab2 << "r2::Camera camera( { 20, 30 }, { 20, 10 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}