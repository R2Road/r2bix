#include "ToolMenu.h"

#include "r2bix/r2bix_Director.h"
#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "texture_viewer/tool_texture_viewer_EntryScene.h"

#include "DevelopmentMenu.h"

r2cm::MenuUp ToolMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> ..."
	) );

	{
		ret->AddItem(
			'a'
			, []()->const char* { return tool_texture_viewer::EntryScene::GetTitle(); }
			, []()->r2cm::eItemLeaveAction
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

				return r2cm::eItemLeaveAction::None;
			}
		);



		ret->AddLineFeed();



		ret->AddSplit();



		ret->AddMenu<DevelopmentMenu>( 27 );
	}

	return ret;
}