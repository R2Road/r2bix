#include "InputMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/item/key_code_viewer.h"
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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', key_code_viewer::Basic() );


		ret->AddLineFeed();


		ret->AddItem( 'q', input_test::MachineeInputCollector_Keyboard() );
		ret->AddItem( 'w', input_test::MachineInputCollector_Mouse() );


		ret->AddLineFeed();


		ret->AddItem( 'a', input_test::KeyboardInputListener_KeyStatus() );
		ret->AddItem( 's', input_test::KeyboardInputListener_Play() );
		ret->AddItem( 'd', input_test::MouseListener_KeyStatus() );
		ret->AddItem( 'f', input_test::MouseListener_Cursor() );


		ret->AddLineFeed();


		ret->AddItem( 'z', input_test::InputManager_Order() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}