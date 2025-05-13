#include "RapidjsonMenu.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "item/rapidjson_test.h"

#include "DevelopmentMenu.h"

r2tm::TitleFunctionT RapidjsonMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Rapidjson";
	};
}
r2tm::DescriptionFunctionT RapidjsonMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> Inprogress : ..."
			"\n"	"> ...";
	};
}
r2tm::WriteFunctionT RapidjsonMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', rapidjson_test::Basic() );



		mp->AddSplit();



		mp->AddMenu( 27, DevelopmentMenu() );
	};
}