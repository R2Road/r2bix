#include "pch.h"
#include "r2research_RootMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"
#include "menu/r2_DevelopMenu.h"

#include "research/flickering_research.h"
#include "research/visible_resource_research.h"

namespace r2research
{
	r2::MenuUp RootMenu::Create( r2::Director& director )
	{
		r2::MenuUp ret( new ( std::nothrow ) r2::Menu(
			director
			, GetTitle(),
			"\n" "> ..."
		) );

		{
			ret->AddChild( '1', visible_resource_research::DrawWithPosition::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( 'q', flickering_research::OneByOne::GetInstance() );
			ret->AddChild( 'w', flickering_research::OneByOne_WithOut_CLS::GetInstance() );
			ret->AddChild( 'e', flickering_research::LineByLine::GetInstance() );
			ret->AddChild( 'r', flickering_research::PageByPage::GetInstance() );
			ret->AddChild( 't', flickering_research::PageByPage_WithOut_CLS_1::GetInstance() );
			ret->AddChild( 'y', flickering_research::PageByPage_WithOut_CLS_2::GetInstance() );


			ret->AddSplit();


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