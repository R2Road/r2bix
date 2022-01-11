#include "pch.h"
#include "r2_ResearchMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"
#include "r2_RootMenu.h"

#include "research/flickering_research.h"

namespace r2
{
	MenuUp ResearchMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
			"\n" "> ..."
		) );

		{
			ret->AddChild( '1', flickering_research::OneByOne::GetInstance() );
			ret->AddChild( '2', flickering_research::LineByLine::GetInstance() );
			ret->AddChild( '3', flickering_research::PageByPage::GetInstance() );
			ret->AddChild( '4', flickering_research::PageByPage_WithOut_CLS::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->eTestResult
				{
					director.Setup( r2::RootMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);
		}

		return ret;
	}
}