#include "pch.h"
#include "RendererMenu.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "renderer_test.h"

r2cm::MenuUp RendererMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddChild( '1', renderer_test::TestRenderable::GetInstance() );
		ret->AddChild( '2', renderer_test::TestRenderer::GetInstance() );

		ret->AddChild( '3', renderer_test::CameraMove1::GetInstance() );
		ret->AddChild( '4', renderer_test::CameraMove2::GetInstance() );


		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eTestEndAction
			{
			director.Setup( TestRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}