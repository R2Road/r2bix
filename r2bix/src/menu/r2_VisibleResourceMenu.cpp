#include "pch.h"
#include "r2_VisibleResourceMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"
#include "r2_RootMenu.h"

#include "test/visible_resource_test.h"

namespace r2
{
	MenuUp VisibleResourceMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', visible_resource_test::FillAll::GetInstance() );
			ret->AddChild( '2', visible_resource_test::Fill::GetInstance() );
			ret->AddChild( '3', visible_resource_test::InitWithChars_1::GetInstance() );
			ret->AddChild( '4', visible_resource_test::InitWithChars_2::GetInstance() );
			ret->AddChild( '5', visible_resource_test::InitWithChars_3::GetInstance() );
			ret->AddChild( '6', visible_resource_test::VisibleRect::GetInstance() );


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