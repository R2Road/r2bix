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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', action_test::TickActionTest() );
		ret->AddItem( '2', action_test::DelayActionTest() );
		ret->AddItem( '3', action_test::SequenceActionTest() );
		ret->AddItem( '4', action_test::MoveByActionTest() );
		ret->AddItem( '5', action_test::MoveToActionTest() );

		ret->AddLineFeed();

		ret->AddItem( 'q', action_test::RepeatActionTest() );
		ret->AddItem( 'w', action_test::BlinkActionTest() );
		ret->AddItem( 'e', action_test::CallbackActionTest() );
		ret->AddItem( 'r', action_test::AnimationRequestActionTest() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}