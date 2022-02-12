#include "pch.h"
#include "r2_DevelopMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"
#include "base/r2base_TestMenu.h"

#include "menu/game/r2game_RootMenu.h"
#include "menu/research/r2research_RootMenu.h"
#include "menu/test/r2test_RootMenu.h"

namespace r2
{
	r2base::NodeUp DevelopMenu::Create( r2base::Director& director )
	{
		r2base::MenuUp ret( new ( std::nothrow ) r2base::TestMenu(
			director
			, GetTitle()
		) );

		{
			ret->AddChild(
				27
				, []()->const char* { return "Exit"; }
				, []()->r2base::eTestEndAction { return r2base::eTestEndAction::Exit; }
			);

			ret->AddLineFeed();

			ret->AddChild(
				'1'
				, []()->const char* { return r2test::RootMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RootMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'2'
				, []()->const char* { return r2research::RootMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2research::RootMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);

			ret->AddLineFeed();
			
			ret->AddChild(
				32
				, []()->const char* { return r2game::RootMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2game::RootMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}