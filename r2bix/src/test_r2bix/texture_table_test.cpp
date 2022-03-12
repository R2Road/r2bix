#include "pch.h"
#include "texture_table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test_r2bix/TextureTable4Test.h"
#include "test_r2bix/Utility4Test.h"

namespace texture_table_test
{
	r2cm::iItem::TitleFuncT TextureTable_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : GetTexture";
		};
	}
	r2cm::iItem::DoFuncT TextureTable_1::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			PROCESS_MAIN( TextureTable4Test::GetInstance().Load() );

			std::cout << r2::linefeed;

			DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "blablabla" ) );

			std::cout << r2::split;

			Utility4Test::DrawTexture( *texture );

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureTable_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : GetTextureFrame";
		};
	}
	r2cm::iItem::DoFuncT TextureTable_2::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			PROCESS_MAIN( TextureTable4Test::GetInstance().Load() );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "test_texture_001" ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( *texture );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto frame = TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTextureFrame( *frame );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureTable_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : Add Texture, Remove Texture";
		};
	}
	r2cm::iItem::DoFuncT TextureTable_3::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				EXPECT_TRUE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2::split;
				
			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( *texture );
			}

			std::cout << r2::split;

			{
				EXPECT_FALSE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2::split;

			{
				EXPECT_TRUE( TextureTable4Test::GetInstance().RemoveTexture( "TextureTable_3" ) );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( *texture );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}