#include "ColorMenu.h"

#include "r2tm/r2tm_MenuProcessor.h"

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
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', color_value_test::Basic() );
		mp->AddItem( '2', color_value_test::ColorMaskOption_Generate() );
		mp->AddItem( '3', color_value_test::ColorMaskOption_On_Off() );
		mp->AddItem( '4', color_value_test::ColorMaskOption_Mask() );


		mp->AddSplit();


		mp->AddMenu( 27, R2bixMenu() );
	};
}