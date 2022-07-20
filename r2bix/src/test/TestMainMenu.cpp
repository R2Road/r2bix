#include "TestMainMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "test/test_miniaudio/TestMiniAudioMenu.h"
#include "test/test_p2048/TestP2048RootMenu.h"
#include "test/test_r2bix/R2bixMenu.h"

r2cm::MenuUp TestMainMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> To do : ..."
	) );

	{
		ret->AddItem(
			'1'
			, []()->const char* { return TestR2bixRootMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestR2bixRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'2'
			, []()->const char* { return TestMiniAudioMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestMiniAudioMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);

		ret->AddLineFeed();

		ret->AddItem(
			'q'
			, []()->const char* { return TestP2048MiniRootMenu::GetTitle(); }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestP2048MiniRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Develop Menu"; }
			, []()->r2cm::eItemLeaveAction
			{
				return r2cm::eItemLeaveAction::Exit;
			}
		);
	}

	return ret;
}