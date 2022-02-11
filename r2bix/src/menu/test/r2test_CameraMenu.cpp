#include "pch.h"
#include "r2test_CameraMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "r2test_RootMenu.h"

#include "test/camera_test.h"

namespace r2
{
	MenuUp CameraMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
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