#include "P2048Menu.h"

#include "r2bix/r2bix_Director.h"
#include "r2tm/r2tm_Director.h"

#include "test_p2048_gameprocessor.h"
#include "test_p2048_numbernode.h"
#include "test_p2048_stage.h"
#include "test_p2048_stageviewnode.h"

#include "DevelopmentMenu.h"

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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', test_p2048_stage::Generate() );
		ret->AddItem( '2', test_p2048_stage::Add_Remove_ClearAll() );
		ret->AddItem( '3', test_p2048_stage::IsIn() );
		ret->AddItem( '4', test_p2048_stage::NumberCount_EmptyCount_IsFull() );
		ret->AddItem( '5', test_p2048_stage::Lock() );
		ret->AddItem( '6', test_p2048_stage::Newcomer() );

		ret->AddLineFeed();

		ret->AddItem( 'q', test_p2048_gameprocessor::MoveReadyTest() );
		ret->AddItem( 'w', test_p2048_gameprocessor::MoveTest() );
		ret->AddItem( 'e', test_p2048_gameprocessor::MergeTest() );
		ret->AddItem( 'r', test_p2048_gameprocessor::MovableCheck() );

		ret->AddLineFeed();

		ret->AddItem( 'a', test_p2048_numbernode::Generate() );
		ret->AddItem( 's', test_p2048_numbernode::SetNumber() );

		ret->AddLineFeed();

		ret->AddItem( 'z', test_p2048_stageviewnode::Generate() );
		ret->AddItem( 'x', test_p2048_stageviewnode::Setup_Render() );
		ret->AddItem( 'c', test_p2048_stageviewnode::UpdateView() );



		ret->AddSplit();



		ret->AddItem(
			32
			, []()->const char* { return p2048::EntryScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( { 107, 53, r2bix_director::Config::eScheduleType::Sleep, 30, 60 } );
				director.Setup( p2048::EntryScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				return r2tm::eDoLeaveAction::None;
			}
		);



		ret->AddSplit();



		ret->AddMenu( 27, DevelopmentMenu() );
	};
}