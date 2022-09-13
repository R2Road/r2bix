#include "TestMenu.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Director.h"

r2cm::MenuUp TestMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> To do : ..."
	) );

	{
		ret->AddSplit();



		ret->AddItem(
			27
			, []()->const char* { return "Return To Develop Menu"; }
			, []()->r2cm::eItemLeaveAction
			{
				return r2cm::eItemLeaveAction::Exit;
			}
		);
	}

	return ret;
}