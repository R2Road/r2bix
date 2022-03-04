#include "pch.h"
#include "r2research_RootScene.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test/item/visible_resource_research.h"

#include "test_r2bix/TestRootMenu.h"

r2test::MenuUp ResearchMenu::Create( r2test::Director& director )
{
	r2test::MenuUp ret( new ( std::nothrow ) r2test::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddChild( '1', visible_resource_research::DrawWithPosition::GetInstance() );


		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Return To Develop Menu"; }
			, [&director]()->r2test::eTestEndAction
			{
				director.Setup( TestRootMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
	}

	return ret;
}