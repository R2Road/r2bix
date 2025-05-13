#include "PSnakeMenu.h"

#include "r2bix_Director.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "psnake/psnake_VersionInfo.h"
#include "psnake/psnake_CompanyScene.h"

#include "DevelopmentMenu.h"


r2tm::TitleFunctionT PSnakeMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "PSnake Menu( To do )";
	};
}
r2tm::DescriptionFunctionT PSnakeMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> Inprogress : ..."
			"\n"	"> ...";
	};
}
r2tm::WriteFunctionT PSnakeMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		//mp->AddItem( '1', test_p2048_stage::Generate::GetInstance() );


		mp->AddSplit();



		mp->AddItem(
			32
			, []()->const char* { return psnake::CompanyScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( psnake::CompanyScene::Create( director ) );

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



		mp->AddMenu( 27, DevelopmentMenu() );
	};
}