#include "menu_color.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test/test_r2bix/menu_r2bix.h"

#include "test_color_value.h"

r2tm::TitleFunctionT Menu_Color::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Color";
	};
}
r2tm::DescriptionFunctionT Menu_Color::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_Color::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_color_value::Basic() );
		mp->AddItem( '2', test_color_value::ColorMaskOption_Generate() );
		mp->AddItem( '3', test_color_value::ColorMaskOption_On_Off() );
		mp->AddItem( '4', test_color_value::ColorMaskOption_Mask() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}