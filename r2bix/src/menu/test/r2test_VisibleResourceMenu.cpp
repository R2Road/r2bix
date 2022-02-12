#include "pch.h"
#include "r2test_VisibleResourceMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"
#include "base/r2base_TestMenu.h"

#include "r2test_RootMenu.h"

#include "test/visible_resource_test.h"

namespace r2test
{
	r2base::NodeUp VisibleResourceMenu::Create( r2base::Director& director )
	{
		r2base::MenuUp ret( new ( std::nothrow ) r2base::TestMenu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', visible_resource_test::FillAll::GetInstance() );
			ret->AddChild( '2', visible_resource_test::Fill::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( 'q', visible_resource_test::InitWithChars_1::GetInstance() );
			ret->AddChild( 'w', visible_resource_test::InitWithChars_2::GetInstance() );
			ret->AddChild( 'e', visible_resource_test::InitWithChars_3::GetInstance() );
			ret->AddChild( 'r', visible_resource_test::InitWithChars_4::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( 'a', visible_resource_test::VisibleRect::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RootMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}