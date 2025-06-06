#include "ToolMenu.h"

#include "r2bix_Director.h"
#include "r2tm/r2tm_MenuProcessor.h"

#include "texture_editor/tool_texture_editor_EntryScene.h"
#include "texture_viewer/tool_texture_viewer_EntryScene.h"

#include "menu_dev.h"

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
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem(
			'a'
			, []()->const char* { return tool_texture_editor::EntryScene::GetTitle(); }
			, []()->r2tm::eDoLeaveAction
			{
				//
				// Setup
				//
				r2bix::Director director( {} );
				director.Setup( tool_texture_editor::EntryScene::Create( director ) );

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

		mp->AddItem(
			's'
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



		mp->AddLineFeed();



		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev() );
	};
}