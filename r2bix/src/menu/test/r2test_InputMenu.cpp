#include "pch.h"
#include "r2test_InputMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "base/r2_TestMenu.h"

#include "r2test_RootMenu.h"

#include "test/key_test.h"
#include "test/window_input_test.h"

namespace r2test
{
	r2::NodeUp InputMenu::Create( r2::Director& director )
	{
		r2::MenuUp ret( new ( std::nothrow ) r2::TestMenu(
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