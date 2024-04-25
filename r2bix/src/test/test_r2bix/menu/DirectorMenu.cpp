#include "DirectorMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "../item/console_screen_buffer_test.h"
#include "../item/screen_buffer_manager_test.h"
#include "../item/director_scheduler_test.h"

r2tm::TitleFunctionT DirectorMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Director";
	};
}
r2tm::DescriptionFunctionT DirectorMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT DirectorMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', console_screen_buffer_test::Basic() );
		ret->AddItem( '2', screen_buffer_manager_test::Basic() );
		ret->AddItem( '3', screen_buffer_manager_test::OriginalBuffer() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem( 'q', director_scheduler_test::Declaration() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}