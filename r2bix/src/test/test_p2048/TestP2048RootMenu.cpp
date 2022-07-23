#include "TestP2048RootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test_p2048_gameprocessor.h"
#include "test_p2048_numbernode.h"
#include "test_p2048_stage.h"
#include "test_p2048_stageviewnode.h"

#include "test/TestMainMenu.h"

r2cm::MenuUp TestP2048MiniRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> 이 게임이 p2048mini 와 다른 것은 이동 과정을 보여준 다는 것에 있다."
		"\n"	"> Inprogress : ..."
		"\n"	"> To do : ..."
	) );

	{
		ret->AddItem( '1', test_p2048_stage::Generate::GetInstance() );
		ret->AddItem( '2', test_p2048_stage::Add_Remove_ClearAll::GetInstance() );
		ret->AddItem( '3', test_p2048_stage::IsIn::GetInstance() );
		ret->AddItem( '4', test_p2048_stage::NumberCount_EmptyCount_IsFull::GetInstance() );
		ret->AddItem( '5', test_p2048_stage::Lock::GetInstance() );
		ret->AddItem( '6', test_p2048_stage::Newcomer::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'q', test_p2048_gameprocessor::MoveReadyTest::GetInstance() );
		ret->AddItem( 'w', test_p2048_gameprocessor::MoveTest::GetInstance() );
		ret->AddItem( 'e', test_p2048_gameprocessor::MergeTest::GetInstance() );
		ret->AddItem( 'r', test_p2048_gameprocessor::MovableCheck::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'a', test_p2048_numbernode::Generate::GetInstance() );
		ret->AddItem( 's', test_p2048_numbernode::SetNumber::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'z', test_p2048_stageviewnode::Generate::GetInstance() );
		ret->AddItem( 'x', test_p2048_stageviewnode::Setup_Render::GetInstance() );
		ret->AddItem( 'c', test_p2048_stageviewnode::UpdateView::GetInstance() );


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