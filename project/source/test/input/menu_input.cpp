#include "menu_input.hpp"

#include "r2tm/r2tm_menu_processor.hpp"

#include "test_input___listener_4_keyboard.hpp"
#include "test_input___key_status_processor.hpp"
#include "test_input___machine_inpue_collector.hpp"
#include "test_input___observation_key_flags.hpp"
#include "test_r2bix_input.hpp"

#include "menu_dev.hpp"

r2tm::TitleFunctionT Menu_R2bix_Input::GetTitleFunction() const
{
	return []()->const char*
	{
		return "r2bix : Input";
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
		mp->AddMessage( "입력 신호( 0, 1 )를 받아온다.", r2tm::eColor::FG_Green );
		mp->AddItem( '1', test_input___machine_inpue_collector::KeyboardStates() );
		mp->AddItem( '2', test_input___machine_inpue_collector::Declaration() );
		mp->AddItem( '3', test_input___machine_inpue_collector::Size_Binary() );
		mp->AddItem( '4', test_input___machine_inpue_collector::Keyboard() );
		mp->AddItem( '5', test_input___machine_inpue_collector::Mouse() );


		mp->AddLineFeed();


		mp->AddMessage( "입력 신호를 상태로 가공", r2tm::eColor::FG_Green );
		mp->AddItem( '7', test_input___key_status_processor::Declaration() );
		mp->AddItem( '8', test_input___key_status_processor::Size_Binary() );
		mp->AddItem( '9', test_input___key_status_processor::Update() );


		mp->AddLineFeed();


		mp->AddMessage( "관측할 키 정보 수집/관리", r2tm::eColor::FG_Green );
		mp->AddItem( 'q', test_input___listener_4_keyboard::ObservationKey() );
		mp->AddItem( 'w', test_input___listener_4_keyboard::ObservationKeyList_Declaration() );
		mp->AddItem( 'e', test_input___listener_4_keyboard::ObservationKeyList_Add() );
		mp->AddItem( 'r', test_input___observation_key_flags::Declaration() );
		mp->AddItem( 't', test_input___observation_key_flags::Size_Binary() );
		mp->AddItem( 'y', test_input___observation_key_flags::Add_Remove() );


		mp->AddLineFeed();


		mp->AddMessage( "Listener", r2tm::eColor::FG_Green );
		mp->AddItem( 'a', test_input::KeyboardInputListener_KeyStatus() );
		mp->AddItem( 's', test_input::KeyboardInputListener_Play() );
		mp->AddItem( 'd', test_input::MouseListener_KeyStatus() );
		mp->AddItem( 'f', test_input::MouseListener_Cursor() );


		mp->AddLineFeed();


		mp->AddMessage( "Manager", r2tm::eColor::FG_Green );
		mp->AddItem( 'z', test_input::InputManager_Order1() );
		mp->AddItem( 'x', test_input::InputManager_Order2() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_Dev() );
	};
}