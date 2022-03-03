#include "pch.h"
#include "r2test_RenderableScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"
#include "test/scene/TestScene.h"

#include "r2test_RootScene.h"
#include "test/item/renderable_test.h"

namespace r2test
{
	r2node::SceneNodeUp RenderableScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle()
		) );

		{
			ret->AddChild( '1', renderable_test::Basic::GetInstance() );


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