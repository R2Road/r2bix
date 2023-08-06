#include "DevelopmentMenu.h"

#include <string>

#include "r2_VersionInfo.h"
#include "r2bix_Director.h"
#include "r2bix_VersionInfo.h"
#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "test/test_miniaudio/MiniAudioMenu.h"
#include "test/test_p2048/P2048Menu.h"
#include "test/test_psnake/PSnakeMenu.h"
#include "test/test_r2bix/R2bixMenu.h"
#include "test/test_rapidjson/RapidjsonMenu.h"

#include "tool/ToolMenu.h"

#include "pmr/pmr_CompanyScene.h"
#include "project_mini_adventure/p_mini_adv_CompanyScene.h"

r2tm::TitleFunctionT DevelopmentMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
				std::string( "Development Menu" )
			+	" : <" + r2tm::VersionInfo.String4Version + ">"
			+	" | <" + r2bix::VersionInfo.String4Version + ">"
			+	" | <" + r2::VersionInfo.String4Version + ">"
		;
		return ret.c_str();
	};
}
r2tm::DescriptionFunctionT DevelopmentMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return r2bix::VersionInfo.String4Road2NextVersion;
	};
}
r2tm::WriteFunctionT DevelopmentMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMenu( '1', R2bixMenu() );
		ret->AddMenu( '2', MiniAudioMenu() );
		ret->AddMenu( '3', RapidjsonMenu() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu( 'q', ToolMenu() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu( 'a', PSnakeMenu() );



		ret->AddLineFeed();
		ret->AddLineFeed();

		

		ret->AddMenu( 's', P2048Menu() );
		ret->AddItem(
			'z'
			, []()->const char* { return p_mini_adv::CompanyScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
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

				return r2tm::eDoLeaveAction::None;
			}
		);
		ret->AddItem(
			'c'
			, []()->const char* { return pmr::CompanyScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
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

				return r2tm::eDoLeaveAction::None;
			}
		);


		
		ret->AddSplit();



		ret->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2tm::eDoLeaveAction
			{
				return r2tm::eDoLeaveAction::Exit;
			}
		);
	};
}