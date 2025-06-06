#include "ProjectAMenu.h"

#include "r2bix_Director.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "project_a/projecta_VersionInfo.h"
#include "project_a/projecta_CompanyScene.h"

#include "menu_dev.h"


r2tm::TitleFunctionT ProjectAMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "ProjectA Menu( In Progress )";
	};
}
r2tm::DescriptionFunctionT ProjectAMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> Inprogress : ..."
			"\n"	"> ...";
	};
}
r2tm::WriteFunctionT ProjectAMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		//mp->AddItem( '1', test_p2048_stage::Generate::GetInstance() );


		mp->AddSplit();



		mp->AddItem(
			32
			, []()->const char* { return projecta::CompanyScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( projecta::CompanyScene::Create( director ) );

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



		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev() );
	};
}