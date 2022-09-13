#include "PSnakeMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "psnake/psnake_VersionInfo.h"

#include "DevelopmentMenu.h"

r2cm::MenuUp PSnakeMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
		, psnake::VersionInfo.String4Road2Version_0_0_1
	) );

	{
		//ret->AddItem( '1', test_p2048_stage::Generate::GetInstance() );


		ret->AddSplit();


		ret->AddMenu<DevelopmentMenu>( 27 );
	}

	return ret;
}