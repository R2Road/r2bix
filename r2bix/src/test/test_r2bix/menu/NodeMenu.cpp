#include "NodeMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "test/test_r2bix/item/node_test.h"

r2cm::MenuUp NodeMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', node_test::Basic::GetInstance() );
		ret->AddItem( '2', node_test::Child::GetInstance() );
		ret->AddItem( 'q', node_test::Scene::GetInstance() );
		ret->AddItem( 'w', node_test::LabelS::GetInstance() );
		ret->AddItem( 'e', node_test::LabelM::GetInstance() );
		ret->AddItem( 'r', node_test::Sprite::GetInstance() );
		ret->AddItem( 't', node_test::SpriteAnimation::GetInstance() );
		ret->AddItem( 'y', node_test::CustomeTexture::GetInstance() );


		ret->AddSplit();


		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}