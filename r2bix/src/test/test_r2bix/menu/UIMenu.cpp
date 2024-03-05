#include "UIMenu.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT UIMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "UI";
	};
}
r2tm::DescriptionFunctionT UIMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT UIMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		//ret->AddMenu<Vector2Menu>( '1' );



		ret->AddSplit();



		ret->AddMenu( 27, R2bixMenu() );
	};
}