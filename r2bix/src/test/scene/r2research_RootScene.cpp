#include "pch.h"
#include "r2research_RootScene.h"

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test/item/visible_resource_research.h"

#include "test/scene/DevelopScene.h"
#include "test/scene/TestScene.h"

namespace r2research
{
	r2node::SceneNodeUp RootScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
			"\n" "> ..."
		) );

		{
			ret->AddChild( '1', visible_resource_research::DrawWithPosition::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]( r2base::Director& )->r2test::eTestEndAction
				{
					director.Setup( DevelopScene::Create( director ) );
					return r2test::eTestEndAction::None;
				}
			);
		}

		return ret;
	}
}