#include "texture_table_test.h"

#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "test/test_r2bix/TextureTable4Test.h"

namespace texture_table_test
{
	r2tm::TitleFunctionT TextureTable_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : GetTexture";
		};
	}
	r2tm::DoFunctionT TextureTable_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			PROCESS_MAIN( TextureTable4Test::GetInstance().Load() );

			LS();

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "blablabla" ) );
				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			LS();

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "test_texture_001" ) );
				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureTable_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : GetTextureFrame";
		};
	}
	r2tm::DoFunctionT TextureTable_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			PROCESS_MAIN( TextureTable4Test::GetInstance().Load() );

			LS();

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "test_texture_001" ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			LS();

			{
				DECLARATION_MAIN( auto frame = TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTextureFrame( *frame );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TextureTable_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : Add Texture, Remove Texture";
		};
	}
	r2tm::DoFunctionT TextureTable_3::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				EXPECT_TRUE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			LS();
				
			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			LS();

			{
				EXPECT_FALSE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			LS();

			{
				EXPECT_TRUE( TextureTable4Test::GetInstance().RemoveTexture( "TextureTable_3" ) );
			}

			LS();

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}