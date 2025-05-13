#include "ActionMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "test/test_r2bix/item/action_test.h"

r2tm::TitleFunctionT ActionMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Action";
	};
}
r2tm::DescriptionFunctionT ActionMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT ActionMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', action_test::TickActionTest() );
		mp->AddItem( '2', action_test::DelayActionTest() );
		mp->AddItem( '3', action_test::SequenceActionTest() );
		mp->AddItem( '4', action_test::MoveByActionTest() );
		mp->AddItem( '5', action_test::MoveToActionTest() );

		mp->AddLineFeed();

		mp->AddItem( 'q', action_test::RepeatActionTest() );
		mp->AddItem( 'w', action_test::BlinkActionTest() );
		mp->AddItem( 'e', action_test::CallbackActionTest() );
		mp->AddItem( 'r', action_test::AnimationRequestActionTest() );


		mp->AddSplit();


		mp->AddMenu( 27, R2bixMenu() );
	};
}