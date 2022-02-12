#include "pch.h"
#include "r2game_RootMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"
#include "base/r2base_TestMenu.h"

#include "menu/DevelopMenu.h"

#include "research/flickering_research.h"
#include "research/visible_resource_research.h"

namespace r2game
{
	r2base::NodeUp RootMenu::Create( r2base::Director& director )
	{
		r2base::MenuUp ret( new ( std::nothrow ) r2base::TestMenu(
			director
			, GetTitle()
		) );

		{
			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( DevelopMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}