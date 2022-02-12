#include "pch.h"
#include "r2test_CameraMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootMenu.h"

#include "scene/TestScene.h"

#include "test/camera_test.h"

namespace r2test
{
	r2base::NodeUp CameraMenu::Create( r2base::Director& director )
	{
		r2base::MenuUp ret( new ( std::nothrow ) r2base::TestMenu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', camera_test::CameraRect::GetInstance() );
			ret->AddChild( '2', camera_test::CameraMove1::GetInstance() );
			ret->AddChild( '3', camera_test::CameraMove2::GetInstance() );


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