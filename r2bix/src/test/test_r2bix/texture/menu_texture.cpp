#include "menu_texture.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test_texture.h"
#include "test_texture_frame.h"
#include "test_texture_table.h"

#include "../R2bixMenu.h"

r2tm::TitleFunctionT Menu_Texture::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Texture, Texture Frame, Texture Table Menu";
	};
}
r2tm::DescriptionFunctionT Menu_Texture::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_Texture::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_texture::FillCharacterAll() );
		mp->AddItem( '2', test_texture::FillCharacter() );
		mp->AddItem( '3', test_texture::FillStringAll() );
		mp->AddItem( '4', test_texture::FillString() );
		mp->AddItem( '5', test_texture::FillColorAll() );
		mp->AddItem( '6', test_texture::FillColor() );
		mp->AddItem( '7', test_texture::FillColorWithMask() );
		mp->AddItem( '8', test_texture::BlendColor() );
		mp->AddItem( '9', test_texture::FillCharacterDisuse() );


		mp->AddLineFeed();


		mp->AddItem( 'q', test_texture::InitWithChars_1() );
		mp->AddItem( 'w', test_texture::InitWithChars_2() );
		mp->AddItem( 'e', test_texture::InitWithChars_3() );
		mp->AddItem( 'r', test_texture::InitWithChars_4() );


		mp->AddLineFeed();
		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'a', test_texture_frame::Basic() );
		mp->AddItem( 's', test_texture_frame::VisibleRect_1() );
		mp->AddItem( 'd', test_texture_frame::VisibleRect_2() );


		mp->AddLineFeed();
		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'z', test_texture_table::TextureTable_1() );
		mp->AddItem( 'x', test_texture_table::TextureTable_2() );
		mp->AddItem( 'c', test_texture_table::TextureTable_3() );


		mp->AddSplit();


		mp->AddMenu( 27, Menu_R2bix() );
	};
}