#include "pch.h"
#include "r2_InputMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"
#include "r2_RootMenu.h"

#include "test/key_test.h"
#include "test/window_input_test.h"

namespace r2
{
	MenuUp InputMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', key_test::Basic::GetInstance() );
			ret->AddChild( '2', window_input_test::Basic::GetInstance() );
			ret->AddChild( '3', window_input_test::Listener::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->eTestResult
				{
					director.Setup( r2::RootMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);
		}

		return ret;
	}
}