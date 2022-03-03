#include "pch.h"
#include "r2test_RendererScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootScene.h"

#include "test/scene/TestScene.h"

#include "test/item/renderer_test.h"

namespace r2test
{
	r2node::SceneNodeUp RendererScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
			"> ..."
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
				, [&director]( r2base::Director& )->r2base::eTestEndAction
				{
					director.Setup( r2test::RootScene::Create( director ) );
					return r2base::eTestEndAction::None;
				}
			);
		}

		return ret;
	}
}