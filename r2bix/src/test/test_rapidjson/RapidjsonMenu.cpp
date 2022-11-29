#include "RapidjsonMenu.h"

#include "r2cm/r2cm_Director.h"

#include "item/rapidjson_test.h"

#include "DevelopmentMenu.h"

r2cm::MenuUp RapidjsonMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> ..."
	) );

	{
		ret->AddItem( '1', rapidjson_test::Basic() );



		ret->AddSplit();



		ret->AddMenu<DevelopmentMenu>( 27 );
	}

	return ret;
}