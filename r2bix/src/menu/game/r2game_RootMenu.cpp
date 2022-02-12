#include "pch.h"
#include "r2game_RootMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "base/r2_TestMenu.h"

#include "menu/r2_DevelopMenu.h"

#include "research/flickering_research.h"
#include "research/visible_resource_research.h"

namespace r2game
{
	r2::NodeUp RootMenu::Create( r2::Director& director )
	{
		r2::MenuUp ret( new ( std::nothrow ) r2::TestMenu(
			director
			, GetTitle()
		) );

		{
			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2::DevelopMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}