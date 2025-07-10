#include "Menu_Dev.h"

#include <string>

#include "r2_VersionInfo.h"
#include "r2bix_Director.h"
#include "r2bix_VersionInfo.h"
#include "r2tm/r2tm_MenuProcessor.h"
#include "r2tm/r2tm_VersionInfo.h"

#include "test/project_a/ProjectAMenu.h"
#include "test/test_p2048/P2048Menu.h"
#include "test/test_psnake/PSnakeMenu.h"
#include "test/test_r2bix/menu_r2bix.h"

#include "tool/ToolMenu.h"

#include "pmr/pmr_CompanyScene.h"
#include "project_mini_adventure/p_mini_adv_CompanyScene.h"

#include "view/menu_view.h"

r2tm::TitleFunctionT Menu_Dev::GetTitleFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
				std::string( "Development" )
			+	" : <" + r2bix::VersionInfo.String4Version + ">"
			+	", <" + r2tm::VersionInfo.String4Version + ">"
			+	", <" + r2::VersionInfo.String4Version + ">"
		;
		return ret.c_str();
	};
}
r2tm::DescriptionFunctionT Menu_Dev::GetDescriptionFunction() const
{
	return []()->const char*
	{
		static const std::string ret =
			std::string()

			+ r2bix::VersionInfo.String4VersionRule
			+ "\n"
			  "\n"
			  "\n"
			+ r2bix::VersionInfo.String4Road2NextVersion
		;
		return ret.c_str();
	};
}
r2tm::WriteFunctionT Menu_Dev::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMenu( '1', Menu_R2bix() );
		mp->AddMenu( '2', ToolMenu() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMenu( 'q', ProjectAMenu() );



		mp->AddLineFeed();
		mp->AddLineFeed();

		

		mp->AddMenu( 'a', PSnakeMenu() );
		mp->AddMenu( 's', P2048Menu() );
		mp->AddItem(
			'd'
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

				//
				// Terminate
				//
				director.Terminate();

				return r2tm::eDoLeaveAction::None;
			}
		);
		mp->AddItem(
			'f'
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

				//
				// Terminate
				//
				director.Terminate();

				return r2tm::eDoLeaveAction::None;
			}
		);



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMenu( 32, Menu_View() );


		
		mp->AddSplit();



		mp->AddItem(
			27
			, []()->const char* { return "Exit"; }
			, []()->r2tm::eDoLeaveAction
			{
				return r2tm::eDoLeaveAction::Exit;
			}
		);
	};
}