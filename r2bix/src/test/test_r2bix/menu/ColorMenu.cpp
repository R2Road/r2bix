#include "ColorMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "test/test_r2bix/item/color_value_test.h"

r2tm::TitleFunctionT ColorMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Color";
	};
}
r2tm::DescriptionFunctionT ColorMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT ColorMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', color_value_test::Basic() );
		ret->AddItem( '2', color_value_test::ColorMaskOption_Generate() );
		ret->AddItem( '3', color_value_test::ColorMaskOption_On_Off() );
		ret->AddItem( '4', color_value_test::ColorMaskOption_Mask() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}