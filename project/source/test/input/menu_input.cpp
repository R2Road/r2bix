#include "menu_input.hpp"

#include "r2tm/r2tm_menu_processor.hpp"

#include "test_input___listener_4_keyboard.hpp"
#include "test_input___listener_4_mouse.hpp"
#include "test_input___key_status_processor.hpp"
#include "test_input___machine_inpue_signals.hpp"
#include "test_input___observation_key_flags.hpp"
#include "test_input___observation_key_list.hpp"
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
		return
			           "# key status processor 의 역활"
			"\n > "    "update 단계에서 키 처리를 하는 간단한 프로그램/데모 제작"
			"\n > "    "전역 단계에서 전체 key 상태를 관측하기 위한 도구"
			"\n\n"
			           "# listener 의 역활"
			"\n > "    "key 처리에 focusing(선택/집중) 이 동반되는 경우 각 focus 별로 key 상태를 따로 관리하기 위한 도구"
		;
	};
}
r2tm::WriteFunctionT Menu_R2bix_Input::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMessage( "입력 신호를 받아 단순하게( 0, 1 ) 가공", r2tm::eColor::FG_Green );
		mp->AddItem( '1', test_input___machine_inpue_signals::KeyboardStates() );
		mp->AddItem( '2', test_input___machine_inpue_signals::Declaration() );
		mp->AddItem( '3', test_input___machine_inpue_signals::Size_Binary() );
		mp->AddItem( '4', test_input___machine_inpue_signals::Keyboard() );
		mp->AddItem( '5', test_input___machine_inpue_signals::Mouse() );


		mp->AddLineFeed();


		mp->AddMessage( "입력 신호를 상태로 가공", r2tm::eColor::FG_Green );
		mp->AddItem( '7', test_input___key_status_processor::Declaration() );
		mp->AddItem( '8', test_input___key_status_processor::Size_Binary() );
		mp->AddItem( '9', test_input___key_status_processor::Update() );


		mp->AddLineFeed();


		mp->AddMessage( "관측할 키 정보 수집/관리", r2tm::eColor::FG_Green );
		mp->AddItem( 'q', test_input___observation_key_list::ObservationKey() );
		mp->AddItem( 'w', test_input___observation_key_list::Declaration() );
		mp->AddItem( 'e', test_input___observation_key_list::Add() );
		mp->AddItem( 'r', test_input___observation_key_flags::Declaration() );
		mp->AddItem( 't', test_input___observation_key_flags::Size_Binary() );
		mp->AddItem( 'y', test_input___observation_key_flags::Add_Remove() );


		mp->AddLineFeed();


		mp->AddMessage( "Listener", r2tm::eColor::FG_Green );
		mp->AddItem( 'a', test_input___listener_4_keyboard::KeyStatus() );
		mp->AddItem( 's', test_input___listener_4_keyboard::Play() );
		mp->AddItem( 'd', test_input___listener_4_mouse::KeyStatus() );
		mp->AddItem( 'f', test_input___listener_4_mouse::Cursor() );


		mp->AddLineFeed();


		mp->AddMessage( "Manager", r2tm::eColor::FG_Green );
		mp->AddItem( 'z', test_input::InputManager_Order1() );
		mp->AddItem( 'x', test_input::InputManager_Order2() );
		mp->AddItem( 'c', test_input::InputManager_Order3() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_Dev() );
	};
}