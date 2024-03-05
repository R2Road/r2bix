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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', miniaudio_test::Engine_Init() );
		ret->AddItem( '2', miniaudio_test::Engine_Config() );
		ret->AddItem( '3', miniaudio_test::Engine_Volume() );
		ret->AddItem( '4', miniaudio_test::Engine_PlaySound() );
		ret->AddItem( '5', miniaudio_test::Engine_Time() );



		ret->AddLineFeed();



		ret->AddItem( 'q', miniaudio_test::Sound_Init_Load() );
		ret->AddItem( 'w', miniaudio_test::Sound_Play() );
		ret->AddItem( 'e', miniaudio_test::Sound_Duplicate() );
		ret->AddItem( 'r', miniaudio_test::Sound_Volume() );
		ret->AddItem( 't', miniaudio_test::Sound_Time() );
		ret->AddItem( 'y', miniaudio_test::Sound_FadeIn() );



		ret->AddLineFeed();



		ret->AddItem( 'a', miniaudio_test::Group_Init() );
		ret->AddItem( 's', miniaudio_test::Group_Volume() );
		ret->AddItem( 'd', miniaudio_test::Group_Time() );



		ret->AddSplit();



		ret->AddMenu( 27, DevelopmentMenu() );
	};
}