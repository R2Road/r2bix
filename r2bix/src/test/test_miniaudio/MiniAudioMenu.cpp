#include "MiniAudioMenu.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Director.h"

#include "item/miniaudio_test.h"

#include "test/TestMenu.h"

r2cm::MenuUp MiniAudioMenu::Create( r2cm::Director& director )
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
		ret->AddItem( 'e', miniaudio_test::Sound_Duplicate::GetInstance() );
		ret->AddItem( 'r', miniaudio_test::Sound_Volume::GetInstance() );
		ret->AddItem( 't', miniaudio_test::Sound_Time::GetInstance() );
		ret->AddItem( 'y', miniaudio_test::Sound_FadeIn::GetInstance() );



		ret->AddLineFeed();



		ret->AddItem( 'a', miniaudio_test::Group_Init::GetInstance() );
		ret->AddItem( 's', miniaudio_test::Group_Volume::GetInstance() );
		ret->AddItem( 'd', miniaudio_test::Group_Time::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<TestMenu>( 27 );
	}

	return ret;
}