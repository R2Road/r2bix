#include "pch.h"
#include "DevelopScene.h"

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "pmr/pmr_CompanyScene.h"
#include "p2048/p2048_CompanyScene.h"
#include "r2research_RootScene.h"
#include "r2test_RootScene.h"

#include "TestScene.h"

r2node::SceneNodeUp DevelopScene::Create( r2base::Director& director )
{
	TestSceneUp ret( new ( std::nothrow ) TestScene(
		director
		, GetTitle()
	) );

	{
		ret->AddChild(
			27
			, []()->const char* { return "Exit"; }
			, []( r2base::Director& )->r2base::eTestEndAction { return r2base::eTestEndAction::Exit; }
		);

		ret->AddLineFeed();

		ret->AddChild(
			'1'
			, []()->const char* { return r2test::RootScene::GetTitle(); }
			, [&director]( r2base::Director& )->r2base::eTestEndAction
			{
				director.Setup( r2test::RootScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);
		ret->AddChild(
			'2'
			, []()->const char* { return r2research::RootScene::GetTitle(); }
			, [&director]( r2base::Director& )->r2base::eTestEndAction
			{
				director.Setup( r2research::RootScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);

		ret->AddLineFeed();
			
		ret->AddChild(
			'z'
			, []()->const char* { return "Game : 2048"; }
			, [&director]( r2base::Director& )->r2base::eTestEndAction
			{
				director.Setup( p2048::CompanyScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);
		ret->AddChild(
			32
			, []()->const char* { return "Game : Mini Rogue"; }
			, [&director]( r2base::Director& )->r2base::eTestEndAction
			{
				director.Setup( pmr::CompanyScene::Create( director ) );
				return r2base::eTestEndAction::None;
			}
		);
	}

	return ret;
}