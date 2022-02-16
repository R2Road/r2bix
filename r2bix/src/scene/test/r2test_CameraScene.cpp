#include "pch.h"
#include "r2test_CameraScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootScene.h"

#include "scene/TestScene.h"

#include "test/camera_test.h"

namespace r2test
{
	r2base::NodeUp CameraScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', camera_test::CameraRect::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RootScene::Create( director ) );
					return r2base::eTestEndAction::None;
				}
			);
		}

		return ret;
	}
}