#include "pch.h"
#include "TestRootMenu.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "CameraMenu.h"
#include "FrameBufferMenu.h"
#include "InputMenu.h"
#include "RenderableMenu.h"
#include "RendererMenu.h"
#include "TextureMenu.h"

#include "animation_test.h"
#include "console_screen_buffer_manager_test.h"
#include "rect_test.h"

#include "visible_resource_research.h"

r2test::MenuUp TestRootMenu::Create( r2test::Director& director )
{
	r2test::MenuUp ret( new ( std::nothrow ) r2test::Menu(
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
		ret->AddChild(
			'1'
			, []()->const char* { return InputMenu::GetTitle(); }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( InputMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
		ret->AddChild( '2', rect_test::Basic::GetInstance() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddChild(
			'q'
			, []()->const char* { return TextureMenu::GetTitle(); }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( TextureMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
		ret->AddChild(
			'w'
			, []()->const char* { return CameraMenu::GetTitle(); }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( CameraMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
		ret->AddChild(
			'e'
			, []()->const char* { return RenderableMenu::GetTitle(); }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( RenderableMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddChild(
			'a'
			, []()->const char* { return FrameBufferMenu::GetTitle(); }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( FrameBufferMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
		ret->AddChild(
			'd'
			, []()->const char* { return RendererMenu::GetTitle(); }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( RendererMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);


		ret->AddChild( 'f', console_screen_buffer_manager_test::Basic::GetInstance() );


		ret->AddSplit();


		ret->AddChild( 'z', animation_test::Basic::GetInstance() );
		ret->AddChild( 'x', visible_resource_research::DrawWithPosition::GetInstance() );


		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Return To Develop Menu"; }
			, []()->r2test::eTestEndAction
			{
				return r2test::eTestEndAction::Exit;
			}
		);
	}

	return ret;
}