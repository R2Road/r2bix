#include "InputMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/item/key_code_viewer.h"
#include "test/test_r2bix/item/r2bix_input_test.h"

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


		ret->AddItem( 'q', r2bix_input_test::TestMachineeInputCollector_Keyboard() );
		ret->AddItem( 'w', r2bix_input_test::TestMachineInputCollector_Mouse() );


		ret->AddLineFeed();


		ret->AddItem( 'a', r2bix_input_test::TestKeyboardInputListener_KeyStatus() );
		ret->AddItem( 's', r2bix_input_test::TestKeyboardInputListener() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}