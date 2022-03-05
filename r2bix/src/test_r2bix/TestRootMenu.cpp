#include "pch.h"
#include "TestRootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "CameraMenu.h"
#include "InputMenu.h"
#include "RenderableMenu.h"
#include "RendererMenu.h"
#include "TextureMenu.h"

#include "animation_test.h"
#include "console_screen_buffer_test.h"
#include "console_screen_buffer_manager_test.h"
#include "rect_test.h"

#include "visible_resource_research.h"

r2cm::MenuUp TestRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : Update Camera Test"
		"\n"	"> To do : Renderer"
		"\n"
		"\n"	"> + Work Flow"
		"\n"	"> Texture"
		"\n"	"> Camera"
		"\n"	"> Renderable"
		"\n"	"> Texture + Camera + Renderable"
		"\n"	"> ..."
	) );

	{
		ret->AddItem( '1', console_screen_buffer_test::Basic::GetInstance() );
		ret->AddItem(
			'2'
			, []()->const char* { return InputMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( InputMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem( '3', rect_test::Basic::GetInstance() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddItem(
			'q'
			, []()->const char* { return TextureMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TextureMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'w'
			, []()->const char* { return CameraMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( CameraMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'e'
			, []()->const char* { return RenderableMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( RenderableMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddItem(
			'a'
			, []()->const char* { return RendererMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( RendererMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem( 's', console_screen_buffer_manager_test::Basic::GetInstance() );


		ret->AddSplit();


		ret->AddItem( 'z', animation_test::Basic::GetInstance() );
		ret->AddItem( 'x', visible_resource_research::DrawWithPosition::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Develop Menu"; }
			, []()->r2cm::eTestEndAction
			{
				return r2cm::eTestEndAction::Exit;
			}
		);
	}

	return ret;
}