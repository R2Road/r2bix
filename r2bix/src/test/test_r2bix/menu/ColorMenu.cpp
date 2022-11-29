#include "ColorMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "test/test_r2bix/item/color_value_test.h"

r2cm::MenuUp ColorMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', color_value_test::Basic() );
		ret->AddItem( '2', color_value_test::ColorMaskOption_Generate() );
		ret->AddItem( '3', color_value_test::ColorMaskOption_On_Off() );
		ret->AddItem( '4', color_value_test::ColorMaskOption_Mask() );


		ret->AddSplit();


		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}