#include "pch.h"
#include "TextureMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test/test_r2bix/TestR2bixRootMenu.h"

#include "test/test_r2bix/item/texture_test.h"
#include "test/test_r2bix/item/texture_frame_test.h"
#include "test/test_r2bix/item/texture_table_test.h"

r2cm::MenuUp TextureMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', texture_test::FillAll::GetInstance() );
		ret->AddItem( '2', texture_test::Fill::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', texture_test::InitWithChars_1::GetInstance() );
		ret->AddItem( 'w', texture_test::InitWithChars_2::GetInstance() );
		ret->AddItem( 'e', texture_test::InitWithChars_3::GetInstance() );
		ret->AddItem( 'r', texture_test::InitWithChars_4::GetInstance() );


		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem( 'a', texture_frame_test::Basic::GetInstance() );
		ret->AddItem( 's', texture_frame_test::VisibleRect_1::GetInstance() );
		ret->AddItem( 'd', texture_frame_test::VisibleRect_2::GetInstance() );


		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem( 'z', texture_table_test::TextureTable_1::GetInstance() );
		ret->AddItem( 'x', texture_table_test::TextureTable_2::GetInstance() );
		ret->AddItem( 'c', texture_table_test::TextureTable_3::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eTestEndAction
			{
			director.Setup( TestR2bixRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}