#include "ToolMenu.h"

#include "r2bix_Director.h"
#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "texture_viewer/tool_texture_viewer_EntryScene.h"

#include "DevelopmentMenu.h"

r2tm::TitleFunctionT ToolMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Tool";
	};
}
r2tm::DescriptionFunctionT ToolMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> Inprogress : ..."
			"\n"	"> ...";
	};
}
r2tm::WriteFunctionT ToolMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem(
			'a'
			, []()->const char* { return tool_texture_viewer::EntryScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( tool_texture_viewer::EntryScene::Create( director ) );

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



		ret->AddLineFeed();



		ret->AddSplit();



		ret->AddMenu( 27, DevelopmentMenu() );
	};
}