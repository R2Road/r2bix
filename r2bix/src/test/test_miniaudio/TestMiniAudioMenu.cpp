#include "pch.h"
#include "TestMiniAudioMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

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
		ret->AddItem( '1', miniaudio_test::Basic::GetInstance() );
		ret->AddItem( '2', miniaudio_test::EngineConfig::GetInstance() );
		ret->AddItem( '3', miniaudio_test::Sound_Load::GetInstance() );
		ret->AddItem( '4', miniaudio_test::Sound_Play::GetInstance() );
		ret->AddItem( '5', miniaudio_test::Sound_Volume::GetInstance() );
		ret->AddItem( '6', miniaudio_test::Group_Init::GetInstance() );
		ret->AddItem( '7', miniaudio_test::Group_Volume::GetInstance() );
		ret->AddItem( '8', miniaudio_test::Engine_Volume::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestMainMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestMainMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}