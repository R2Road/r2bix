#include "pch.h"
#include "r2game_RootMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "research/flickering_research.h"
#include "research/visible_resource_research.h"

#include "scene/DevelopScene.h"
#include "scene/TestScene.h"

namespace r2game
{
	r2base::NodeUp RootMenu::Create( r2base::Director& director )
	{
		MenuUp ret( new ( std::nothrow ) TestMenu(
			director
			, GetTitle()
		) );

		{
			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( DevelopScene::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}