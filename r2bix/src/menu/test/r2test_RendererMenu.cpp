#include "pch.h"
#include "r2test_RendererMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "r2test_RootMenu.h"

#include "test/renderer_test.h"

namespace r2
{
	MenuUp RendererMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', renderer_test::TestRenderable::GetInstance() );
			ret->AddChild( '2', renderer_test::TestRenderer::GetInstance() );


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