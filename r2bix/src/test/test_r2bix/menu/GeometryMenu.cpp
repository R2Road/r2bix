#include "GeometryMenu.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT GeometryMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Geometry";
	};
}
r2tm::DescriptionFunctionT GeometryMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT GeometryMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		//mp->AddMenu<Vector2Menu>( '1' );



		mp->AddSplit();



		mp->AddMenu( 27, R2bixMenu() );
	};
}