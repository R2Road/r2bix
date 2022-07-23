#include "TestMenu.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Director.h"

#include "test/test_miniaudio/MiniAudioMenu.h"
#include "test/test_p2048/P2048Menu.h"
#include "test/test_r2bix/R2bixMenu.h"

r2cm::MenuUp TestMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> To do : ..."
	) );

	{
		ret->AddMenu<R2bixMenu>( '1' );
		ret->AddMenu<MiniAudioMenu>( '2' );



		ret->AddLineFeed();



		ret->AddMenu<P2048Menu>( 'q' );



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