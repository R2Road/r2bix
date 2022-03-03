#include "pch.h"
#include "r2test_FrameBufferScene.h"

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "r2test_RootScene.h"
#include "TestScene.h"

#include "test/item/framebuffer_test.h"

namespace r2test
{
	r2node::SceneNodeUp FrameBufferScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', framebuffer_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]( r2base::Director& )->r2test::eTestEndAction
				{
					director.Setup( r2test::RootScene::Create( director ) );
					return r2test::eTestEndAction::None;
				}
			);
		}

		return ret;
	}
}