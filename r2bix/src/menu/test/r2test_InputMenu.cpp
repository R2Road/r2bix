#include "pch.h"
#include "r2test_InputMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootMenu.h"

#include "scene/TestScene.h"

#include "test/key_test.h"
#include "test/window_input_test.h"

namespace r2test
{
	r2base::NodeUp InputMenu::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', key_test::Basic::GetInstance() );
			ret->AddChild( '2', window_input_test::TestKeyboardInputCollector::GetInstance() );


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