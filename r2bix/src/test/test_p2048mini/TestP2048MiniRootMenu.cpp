#include "pch.h"
#include "TestP2048MiniRootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test/test_p2048mini/item/test_stage.h"

#include "test/TestMainMenu.h"

r2cm::MenuUp TestP2048MiniRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : Stage : Move"
		"\n"	"> To do : ..."
	) );

	{
		ret->AddItem( '1', test_stage::Basic::GetInstance() );
		ret->AddItem( '2', test_stage::StageViewNodeTest_1::GetInstance() );
		ret->AddItem( '3', test_stage::StageViewNodeTest_2::GetInstance() );
		ret->AddItem( '4', test_stage::MoveReadyTest::GetInstance() );
		ret->AddItem( '5', test_stage::MoveTest::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestMainMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestMainMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}