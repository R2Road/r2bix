#include "P2048Menu.h"

#include "r2bix_Director.h"
#include "r2tm/r2tm_MenuProcessor.h"

#include "test_p2048_gameprocessor.h"
#include "test_p2048_numbernode.h"
#include "test_p2048_stage.h"
#include "test_p2048_stageviewnode.h"

#include "menu_dev.h"

#include "p2048/p2048_EntryScene.h"

r2tm::TitleFunctionT P2048Menu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "P2048 Menu( To do )";
	};
}
r2tm::DescriptionFunctionT P2048Menu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> 이 게임이 p2048mini 와 다른 것은 이동 과정을 보여준 다는 것에 있다."
			"\n"	"> 방치중..."
		;
	};
}
r2tm::WriteFunctionT P2048Menu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_p2048_stage::Generate() );
		mp->AddItem( '2', test_p2048_stage::Add_Remove_ClearAll() );
		mp->AddItem( '3', test_p2048_stage::IsIn() );
		mp->AddItem( '4', test_p2048_stage::NumberCount_EmptyCount_IsFull() );
		mp->AddItem( '5', test_p2048_stage::Lock() );
		mp->AddItem( '6', test_p2048_stage::Newcomer() );

		mp->AddLineFeed();

		mp->AddItem( 'q', test_p2048_gameprocessor::MoveReadyTest() );
		mp->AddItem( 'w', test_p2048_gameprocessor::MoveTest() );
		mp->AddItem( 'e', test_p2048_gameprocessor::MergeTest() );
		mp->AddItem( 'r', test_p2048_gameprocessor::MovableCheck() );

		mp->AddLineFeed();

		mp->AddItem( 'a', test_p2048_numbernode::Generate() );
		mp->AddItem( 's', test_p2048_numbernode::SetNumber() );

		mp->AddLineFeed();

		mp->AddItem( 'z', test_p2048_stageviewnode::Generate() );
		mp->AddItem( 'x', test_p2048_stageviewnode::Setup_Render() );
		mp->AddItem( 'c', test_p2048_stageviewnode::UpdateView() );



		mp->AddSplit();



		mp->AddItem(
			32
			, []()->const char* { return p2048::EntryScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( { 107, 53, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );
				director.Setup( p2048::EntryScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				//
				// Terminate
				//
				director.Terminate();

				return r2tm::eDoLeaveAction::None;
			}
		);



		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev() );
	};
}