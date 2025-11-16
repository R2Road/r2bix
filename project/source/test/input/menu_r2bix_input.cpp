#include "menu_r2bix_input.hpp"

#include "r2tm/r2tm_menu_processor.hpp"

#include "test_input___machine_inpue_collector.hpp"
#include "test_r2bix_input.hpp"

#include "menu_dev.hpp"

r2tm::TitleFunctionT Menu_R2bix_Input::GetTitleFunction() const
{
	return []()->const char*
	{
		return "rxbix : Input";
	};
}
r2tm::DescriptionFunctionT Menu_R2bix_Input::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_R2bix_Input::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_input___machine_inpue_collector::MachineInputCollector_Declaration() );
		mp->AddItem( '2', test_input___machine_inpue_collector::MachineInputCollector_Keyboard() );
		mp->AddItem( '3', test_input___machine_inpue_collector::MachineInputCollector_Mouse() );


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


		mp->AddMenu( 27, Menu_Dev() );
	};
}