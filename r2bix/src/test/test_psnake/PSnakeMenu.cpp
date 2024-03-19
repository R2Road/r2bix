#include "PSnakeMenu.h"

#include "r2bix_Director.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "psnake/psnake_VersionInfo.h"
#include "psnake/psnake_CompanyScene.h"

#include "DevelopmentMenu.h"


r2tm::TitleFunctionT PSnakeMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "PSnake Menu( In Progress )";
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
	return []( r2tm::MenuProcessor* ret )
	{
		//ret->AddItem( '1', test_p2048_stage::Generate::GetInstance() );


		ret->AddSplit();



		ret->AddItem(
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



		ret->AddSplit();



		ret->AddMenu( 27, DevelopmentMenu() );
	};
}