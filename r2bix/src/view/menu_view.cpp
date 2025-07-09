#include "Menu_View.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "view/view_key.h"
#include "view/view_terminal_info.h"

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
		mp->AddItem( '1', view_key::Do());
		mp->AddItem( '2', view_terminal_info::Basic() );


		
		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev()	);
	};
}