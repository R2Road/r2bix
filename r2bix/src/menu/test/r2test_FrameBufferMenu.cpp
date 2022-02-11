#include "pch.h"
#include "r2test_FrameBufferMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "r2test_RootMenu.h"

#include "test/framebuffer_test.h"

namespace r2test
{
	r2::MenuUp FrameBufferMenu::Create( r2::Director& director )
	{
		r2::MenuUp ret( new ( std::nothrow ) r2::Menu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', framebuffer_test::Basic::GetInstance() );
			ret->AddChild( '2', framebuffer_test::DrawAtOnce::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2test::RootMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}