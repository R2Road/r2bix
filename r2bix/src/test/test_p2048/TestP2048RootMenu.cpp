#include "TestP2048RootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "test_p2048_stage.h"
#include "test_p2048_stageviewnode.h"

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
		ret->AddItem( '1', test_p2048_stage::Basic::GetInstance() );
		ret->AddItem( '2', test_p2048_stage::MoveReadyTest::GetInstance() );
		ret->AddItem( '3', test_p2048_stage::MoveTest::GetInstance() );
		ret->AddItem( '4', test_p2048_stage::MergeTest::GetInstance() );
		ret->AddItem( '5', test_p2048_stage::EmptyCheck::GetInstance() );
		ret->AddItem( '6', test_p2048_stage::MovableCheck::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'q', test_p2048_stageviewnode::Generate::GetInstance() );
		ret->AddItem( 'w', test_p2048_stageviewnode::Setup_Render::GetInstance() );
		ret->AddItem( 'e', test_p2048_stageviewnode::UpdateView::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestMainMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestMainMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}