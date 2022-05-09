#include "pch.h"
#include "TestMiniAudioMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "item/miniaudio_test.h"

#include "test/TestMainMenu.h"

r2cm::MenuUp TestMiniAudioMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> ..."
	) );

	{
		ret->AddItem( '1', miniaudio_test::Engine_Init::GetInstance() );
		ret->AddItem( '2', miniaudio_test::Engine_Config::GetInstance() );
		ret->AddItem( '3', miniaudio_test::Engine_Volume::GetInstance() );
		ret->AddItem( '4', miniaudio_test::Engine_PlaySound::GetInstance() );
		ret->AddItem( '5', miniaudio_test::Engine_Time::GetInstance() );



		ret->AddLineFeed();



		ret->AddItem( 'q', miniaudio_test::Sound_Init_Load::GetInstance() );
		ret->AddItem( 'w', miniaudio_test::Sound_Play::GetInstance() );
		ret->AddItem( 'e', miniaudio_test::Sound_Volume::GetInstance() );
		ret->AddItem( 'r', miniaudio_test::Sound_Time::GetInstance() );
		ret->AddItem( 't', miniaudio_test::Sound_FadeIn::GetInstance() );



		ret->AddLineFeed();



		ret->AddItem( 'a', miniaudio_test::Group_Init::GetInstance() );
		ret->AddItem( 's', miniaudio_test::Group_Volume::GetInstance() );



		ret->AddSplit();



		ret->AddItem(
			27
			, []()->const char* { return TestMainMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestMainMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}