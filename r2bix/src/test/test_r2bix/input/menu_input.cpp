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
		mp->AddItem( '1', test_input::MachineeInputCollector_Keyboard() );
		mp->AddItem( '2', test_input::MachineInputCollector_Mouse() );


		mp->AddLineFeed();


		mp->AddItem( 'q', test_input::ObservationKey() );


		mp->AddLineFeed();


		mp->AddItem( 'a', test_input::KeyboardInputListener_KeyStatus() );
		mp->AddItem( 's', test_input::KeyboardInputListener_Play() );
		mp->AddItem( 'd', test_input::MouseListener_KeyStatus() );
		mp->AddItem( 'f', test_input::MouseListener_Cursor() );


		mp->AddLineFeed();


		mp->AddItem( 'z', test_input::InputManager_Order1() );
		mp->AddItem( 'x', test_input::InputManager_Order2() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}