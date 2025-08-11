#include "menu_tool.hpp"

#include "r2bix_Director.h"
#include "r2tm/r2tm_MenuProcessor.h"

#include "texture_editor/tool_texture_editor_EntryScene.h"
#include "texture_viewer/tool_texture_viewer_EntryScene.h"

#include "menu_dev.hpp"

r2tm::TitleFunctionT Menu_Tool::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Tool";
	};
}
r2tm::DescriptionFunctionT Menu_Tool::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
			        "### 작업 상황 ###"
			"\n"
			"\n"    "[~] " "Texture Editor"
			"\n"	"[ ] " "Texture Viewer";
	};
}
r2tm::WriteFunctionT Menu_Tool::GetWriteFunction() const
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

		mp->AddItem(
			's'
			, []()->const char*
			{
				return tool_texture_viewer::EntryScene::GetTitle();
			}
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