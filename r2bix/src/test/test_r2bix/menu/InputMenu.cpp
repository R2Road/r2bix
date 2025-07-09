#include "InputMenu.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test/test_r2bix/item/input_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT InputMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Input";
	};
}
r2tm::DescriptionFunctionT InputMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT InputMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', input_test::MachineeInputCollector_Keyboard() );
		mp->AddItem( '2', input_test::MachineInputCollector_Mouse() );


		mp->AddLineFeed();


		mp->AddItem( 'q', input_test::ObservationKey() );


		mp->AddLineFeed();


		mp->AddItem( 'a', input_test::KeyboardInputListener_KeyStatus() );
		mp->AddItem( 's', input_test::KeyboardInputListener_Play() );
		mp->AddItem( 'd', input_test::MouseListener_KeyStatus() );
		mp->AddItem( 'f', input_test::MouseListener_Cursor() );


		mp->AddLineFeed();


		mp->AddItem( 'z', input_test::InputManager_Order1() );
		mp->AddItem( 'x', input_test::InputManager_Order2() );


		mp->AddSplit();


		mp->AddMenu( 27, R2bixMenu() );
	};
}