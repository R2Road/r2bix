#include "pch.h"
#include "r2test_RendererMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootMenu.h"

#include "scene/TestScene.h"

#include "test/renderer_test.h"

namespace r2test
{
	r2base::NodeUp RendererMenu::Create( r2base::Director& director )
	{
		MenuUp ret( new ( std::nothrow ) TestMenu(
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
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RootMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}