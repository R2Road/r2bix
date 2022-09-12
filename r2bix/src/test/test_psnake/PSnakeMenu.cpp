#include "PSnakeMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/TestMenu.h"

r2cm::MenuUp PSnakeMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		//ret->AddItem( '1', test_p2048_stage::Generate::GetInstance() );


		ret->AddSplit();


		ret->AddMenu<TestMenu>( 27 );
	}

	return ret;
}