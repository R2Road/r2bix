#include "pch.h"
#include "r2_FrameBufferMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "r2test_RootMenu.h"

#include "test/framebuffer_test.h"

namespace r2
{
	MenuUp FrameBufferMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
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
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::RootMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}