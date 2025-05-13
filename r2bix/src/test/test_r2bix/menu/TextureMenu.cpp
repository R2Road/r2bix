#include "TextureMenu.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "test/test_r2bix/item/texture_test.h"
#include "test/test_r2bix/item/texture_frame_test.h"
#include "test/test_r2bix/item/texture_table_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT TextureMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Texture, Texture Frame, Texture Table Menu";
	};
}
r2tm::DescriptionFunctionT TextureMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT TextureMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', texture_test::FillCharacterAll() );
		mp->AddItem( '2', texture_test::FillCharacter() );
		mp->AddItem( '3', texture_test::FillStringAll() );
		mp->AddItem( '4', texture_test::FillString() );
		mp->AddItem( '5', texture_test::FillColorAll() );
		mp->AddItem( '6', texture_test::FillColor() );
		mp->AddItem( '7', texture_test::FillColorWithMask() );
		mp->AddItem( '8', texture_test::BlendColor() );
		mp->AddItem( '9', texture_test::FillCharacterDisuse() );


		mp->AddLineFeed();


		mp->AddItem( 'q', texture_test::InitWithChars_1() );
		mp->AddItem( 'w', texture_test::InitWithChars_2() );
		mp->AddItem( 'e', texture_test::InitWithChars_3() );
		mp->AddItem( 'r', texture_test::InitWithChars_4() );


		mp->AddLineFeed();
		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'a', texture_frame_test::Basic() );
		mp->AddItem( 's', texture_frame_test::VisibleRect_1() );
		mp->AddItem( 'd', texture_frame_test::VisibleRect_2() );


		mp->AddLineFeed();
		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'z', texture_table_test::TextureTable_1() );
		mp->AddItem( 'x', texture_table_test::TextureTable_2() );
		mp->AddItem( 'c', texture_table_test::TextureTable_3() );


		mp->AddSplit();


		mp->AddMenu( 27, R2bixMenu() );
	};
}