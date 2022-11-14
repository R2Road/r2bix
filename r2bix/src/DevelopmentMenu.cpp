#include "DevelopmentMenu.h"

#include <string>

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_VersionInfo.h"
#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_VersionInfo.h"

#include "test/test_miniaudio/MiniAudioMenu.h"
#include "test/test_p2048/P2048Menu.h"
#include "test/test_psnake/PSnakeMenu.h"
#include "test/test_r2bix/R2bixMenu.h"

#include "tool/ToolMenu.h"

#include "pmr/pmr_CompanyScene.h"
#include "project_mini_adventure/p_mini_adv_CompanyScene.h"

const char* DevelopmentMenu::GetTitle()
{
	static const std::string ret =
		std::string( "Development Menu" )
		+ " : <" + r2cm::VersionInfo.String4Version + ">"
		+ " : <" + r2bix::VersionInfo.String4Version + ">";
	return ret.c_str();
}

r2cm::MenuUp DevelopmentMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, r2bix::VersionInfo.String4Road2Version_0_0_3
	) );

	{
		ret->AddMenu<R2bixMenu>( '1' );
		ret->AddMenu<MiniAudioMenu>( '2' );



		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu<ToolMenu>( 'q' );



		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu<PSnakeMenu>( 'a' );



		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();

		

		ret->AddMenu<P2048Menu>( 's' );
		ret->AddItem(
			'z'
			, []()->const char* { return p_mini_adv::CompanyScene::GetTitle(); }
			, []()->r2cm::eItemLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( p_mini_adv::CompanyScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				return r2cm::eItemLeaveAction::None;
			}
		);
		ret->AddItem(
			'c'
			, []()->const char* { return pmr::CompanyScene::GetTitle(); }
			, []()->r2cm::eItemLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( pmr::CompanyScene::Create( director ) );

				//
				// Process
				//
				director.Run();

				return r2cm::eItemLeaveAction::None;
			}
		);


		
		ret->AddSplit();



		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2cm::eItemLeaveAction
			{
				return r2cm::eItemLeaveAction::Exit;
			}
		);
	}

	return ret;
}