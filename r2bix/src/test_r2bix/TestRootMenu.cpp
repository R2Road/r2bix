#include "pch.h"
#include "TestRootMenu.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

r2test::MenuUp TestRootMenu::Create( r2test::Director& director )
{
	r2test::MenuUp ret( new ( std::nothrow ) r2test::Menu(
		director
		, GetTitle(),
		"> Inprogress : BlaBla"
		"\n"	"> To do : BlaBla"
	) );

	{
		//ret->AddChild( '1', empty_test::Basic::GetInstance() );

		ret->AddLineFeed();

		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Exit"; }
		, []()->r2test::eTestEndAction { return r2test::eTestEndAction::Exit; }
		);
	}

	return ret;
}