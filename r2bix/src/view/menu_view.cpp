#include "Menu_View.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "view/key_view.h"
#include "view/terminal_info_view.h"

#include "../menu_dev.h"

r2tm::TitleFunctionT Menu_View::GetTitleFunction() const
{
	return []()->const char*
	{
		return "View";
	};
}
r2tm::DescriptionFunctionT Menu_View::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_View::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', key_view::Do());
		mp->AddItem( '2', terminal_info_view::Basic() );


		
		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev()	);
	};
}