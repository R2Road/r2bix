#include "pch.h"
#include "DevelopScene.h"

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "pmr/pmr_CompanyScene.h"
#include "p2048/p2048_CompanyScene.h"

r2node::SceneNodeUp DevelopScene::Create( r2base::Director& director )
{
	//TestSceneUp ret( new ( std::nothrow ) TestScene(
	//	director
	//	, GetTitle()
	//) );

	//{
	//	ret->AddChild(
	//		27
	//		, []()->const char* { return "Exit"; }
	//		, []( r2base::Director& )->r2test::eTestEndAction { return r2test::eTestEndAction::Exit; }
	//	);

	//	ret->AddLineFeed();

	//	

	//	ret->AddLineFeed();
	//		
	//	ret->AddChild(
	//		'z'
	//		, []()->const char* { return "Game : 2048"; }
	//		, [&director]( r2base::Director& )->r2test::eTestEndAction
	//		{
	//			director.Setup( p2048::CompanyScene::Create( director ) );
	//			return r2test::eTestEndAction::None;
	//		}
	//	);
	//	ret->AddChild(
	//		32
	//		, []()->const char* { return "Game : Mini Rogue"; }
	//		, [&director]( r2base::Director& )->r2test::eTestEndAction
	//		{
	//			director.Setup( pmr::CompanyScene::Create( director ) );
	//			return r2test::eTestEndAction::None;
	//		}
	//	);
	//}

	return nullptr;
}