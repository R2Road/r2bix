#include "pch.h"
#include "RenderableMenu.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "renderable_test.h"

r2cm::MenuUp RenderableMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddChild( '1', renderable_test::Basic::GetInstance() );


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