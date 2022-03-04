#include "pch.h"
#include "FrameBufferMenu.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "framebuffer_test.h"

r2test::MenuUp FrameBufferMenu::Create( r2test::Director& director )
{
	r2test::MenuUp ret( new ( std::nothrow ) r2test::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddChild( '1', framebuffer_test::Basic::GetInstance() );


		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( TestRootMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
	}

	return ret;
}