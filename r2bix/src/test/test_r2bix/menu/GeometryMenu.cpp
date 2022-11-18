#include "GeometryMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "Vector2Menu.h"
#include "Vector3Menu.h"

#include "test/test_r2bix/R2bixMenu.h"

r2cm::MenuUp GeometryMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddMenu<Vector2Menu>( '1' );
		ret->AddMenu<Vector3Menu>( '2' );



		ret->AddSplit();



		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}