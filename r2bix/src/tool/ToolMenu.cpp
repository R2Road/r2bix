#include "ToolMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "DevelopmentMenu.h"

r2cm::MenuUp ToolMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> ..."
	) );

	{



		ret->AddLineFeed();



		ret->AddSplit();



		ret->AddMenu<DevelopmentMenu>( 27 );
	}

	return ret;
}