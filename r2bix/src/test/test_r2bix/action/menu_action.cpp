#include "menu_action.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "../R2bixMenu.h"

#include "test_action.h"

r2tm::TitleFunctionT Menu_Action::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Action";
	};
}
r2tm::DescriptionFunctionT Menu_Action::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_Action::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_action::TickActionTest() );
		mp->AddItem( '2', test_action::DelayActionTest() );
		mp->AddItem( '3', test_action::SequenceActionTest() );
		mp->AddItem( '4', test_action::MoveByActionTest() );
		mp->AddItem( '5', test_action::MoveToActionTest() );

		mp->AddLineFeed();

		mp->AddItem( 'q', test_action::RepeatActionTest() );
		mp->AddItem( 'w', test_action::BlinkActionTest() );
		mp->AddItem( 'e', test_action::CallbackActionTest() );
		mp->AddItem( 'r', test_action::AnimationRequestActionTest() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}