#include "menu_input.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test_input.h"

#include "../R2bixMenu.h"

r2tm::TitleFunctionT Menu_Input::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Input";
	};
}
r2tm::DescriptionFunctionT Menu_Input::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_Input::GetWriteFunction() const
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