#include "pch.h"
#include "r2_DevelopMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"

#include "menu/research/r2research_RootMenu.h"
#include "menu/test/r2test_RootMenu.h"

namespace r2
{
	MenuUp DevelopMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle()
		) );

		{
			ret->AddChild(
				27
				, []()->const char* { return "Exit"; }
				, []()->eTestEndAction { return eTestEndAction::Exit; }
			);

			ret->AddLineFeed();

			ret->AddChild(
				'1'
				, []()->const char* { return r2test::RootMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2test::RootMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'2'
				, []()->const char* { return r2research::RootMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2research::RootMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);


			
		}

		return ret;
	}
}