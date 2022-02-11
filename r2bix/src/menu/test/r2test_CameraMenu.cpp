#include "pch.h"
#include "r2test_CameraMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "r2test_RootMenu.h"

#include "test/camera_test.h"

namespace r2test
{
	r2::MenuUp CameraMenu::Create( r2::Director& director )
	{
		r2::MenuUp ret( new ( std::nothrow ) r2::Menu(
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