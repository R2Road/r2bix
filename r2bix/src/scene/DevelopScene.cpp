#include "pch.h"
#include "DevelopScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "menu/game/r2game_RootMenu.h"
#include "menu/research/r2research_RootMenu.h"
#include "menu/test/r2test_RootMenu.h"

#include "scene/TestScene.h"

r2base::NodeUp DevelopScene::Create( r2base::Director& director )
{
	MenuUp ret( new ( std::nothrow ) TestScene(
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