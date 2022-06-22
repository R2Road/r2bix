#include "ColorMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "test/test_r2bix/TestR2bixRootMenu.h"

#include "test/test_r2bix/item/color_value_test.h"

r2cm::MenuUp ColorMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', color_value_test::Basic::GetInstance() );
		ret->AddItem( '2', color_value_test::ColorMaskOption_Generate::GetInstance() );
		ret->AddItem( '3', color_value_test::ColorMaskOption_On_Off::GetInstance() );
		ret->AddItem( '4', color_value_test::ColorMaskOption_Mask::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eItemLeaveAction
			{
			director.Setup( TestR2bixRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}