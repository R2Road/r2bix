#include "NodeMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/test_r2bix/item/node_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2cm::MenuUp NodeMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', node_test::Basic() );
		ret->AddItem( '2', node_test::Child_Count() );
		ret->AddItem( '3', node_test::Child_Sequence() );



		ret->AddLineFeed();



		ret->AddItem( 'q', node_test::Scene() );
		ret->AddItem( 'w', node_test::LabelS() );
		ret->AddItem( 'e', node_test::LabelM() );
		ret->AddItem( 'r', node_test::Sprite() );
		ret->AddItem( 't', node_test::SpriteAnimation() );
		ret->AddItem( 'y', node_test::CustomeTexture() );



		ret->AddSplit();



		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}