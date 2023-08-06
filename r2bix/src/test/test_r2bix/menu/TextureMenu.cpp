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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', texture_test::FillCharacterAll() );
		ret->AddItem( '2', texture_test::FillCharacter() );
		ret->AddItem( '3', texture_test::FillColorAll() );
		ret->AddItem( '4', texture_test::FillColor() );
		ret->AddItem( '5', texture_test::FillColorWithMask() );
		ret->AddItem( '6', texture_test::BlendColor() );
		ret->AddItem( '7', texture_test::FillCharacterDisuse() );


		ret->AddLineFeed();


		ret->AddItem( 'q', texture_test::InitWithChars_1() );
		ret->AddItem( 'w', texture_test::InitWithChars_2() );
		ret->AddItem( 'e', texture_test::InitWithChars_3() );
		ret->AddItem( 'r', texture_test::InitWithChars_4() );


		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem( 'a', texture_frame_test::Basic() );
		ret->AddItem( 's', texture_frame_test::VisibleRect_1() );
		ret->AddItem( 'd', texture_frame_test::VisibleRect_2() );


		ret->AddLineFeed();
		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddItem( 'z', texture_table_test::TextureTable_1() );
		ret->AddItem( 'x', texture_table_test::TextureTable_2() );
		ret->AddItem( 'c', texture_table_test::TextureTable_3() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}