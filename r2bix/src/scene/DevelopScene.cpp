#include "pch.h"
#include "DevelopScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "scene/game/r2game_RootScene.h"
#include "scene/research/r2research_RootScene.h"
#include "scene/test/r2test_RootScene.h"

#include "scene/TestScene.h"

r2base::NodeUp DevelopScene::Create( r2base::Director& director )
{
	TestSceneUp ret( new ( std::nothrow ) TestScene(
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
			, []()->const char* { return r2test::RootScene::GetTitle(); }
			, [&director]()->r2base::eTestEndAction
			{
				director.Setup( r2test::RootScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);
		ret->AddChild(
			'2'
			, []()->const char* { return r2research::RootScene::GetTitle(); }
			, [&director]()->r2base::eTestEndAction
			{
				director.Setup( r2research::RootScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);

		ret->AddLineFeed();
			
		ret->AddChild(
			32
			, []()->const char* { return r2game::RootScene::GetTitle(); }
			, [&director]()->r2base::eTestEndAction
			{
				director.Setup( r2game::RootScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);
	}

	return ret;
}