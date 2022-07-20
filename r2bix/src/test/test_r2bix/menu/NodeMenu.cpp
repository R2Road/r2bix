#include "NodeMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

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
		ret->AddItem( '2', node_test::Scene::GetInstance() );
		ret->AddItem( '3', node_test::LabelS::GetInstance() );
		ret->AddItem( '4', node_test::LabelM::GetInstance() );
		ret->AddItem( '5', node_test::Sprite::GetInstance() );
		ret->AddItem( '6', node_test::SpriteAnimation::GetInstance() );
		ret->AddItem( '7', node_test::CustomeTexture::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestR2bixRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}