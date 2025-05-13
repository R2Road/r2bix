#include "MiniAudioMenu.h"

#include "r2tm/r2tm_Director.h"

#include "item/miniaudio_test.h"

#include "DevelopmentMenu.h"

r2tm::TitleFunctionT MiniAudioMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "MiniAudio : v0.11.9";
	};
}
r2tm::DescriptionFunctionT MiniAudioMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> Inprogress : ..."
			"\n"	"> ...";
	};
}
r2tm::WriteFunctionT MiniAudioMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', miniaudio_test::Engine_Init() );
		mp->AddItem( '2', miniaudio_test::Engine_Config() );
		mp->AddItem( '3', miniaudio_test::Engine_Volume() );
		mp->AddItem( '4', miniaudio_test::Engine_PlaySound() );
		mp->AddItem( '5', miniaudio_test::Engine_Time() );



		mp->AddLineFeed();



		mp->AddItem( 'q', miniaudio_test::Sound_Init_Load() );
		mp->AddItem( 'w', miniaudio_test::Sound_Play() );
		mp->AddItem( 'e', miniaudio_test::Sound_Duplicate() );
		mp->AddItem( 'r', miniaudio_test::Sound_Volume() );
		mp->AddItem( 't', miniaudio_test::Sound_Time() );
		mp->AddItem( 'y', miniaudio_test::Sound_FadeIn() );



		mp->AddLineFeed();



		mp->AddItem( 'a', miniaudio_test::Group_Init() );
		mp->AddItem( 's', miniaudio_test::Group_Volume() );
		mp->AddItem( 'd', miniaudio_test::Group_Time() );



		mp->AddSplit();



		mp->AddMenu( 27, DevelopmentMenu() );
	};
}