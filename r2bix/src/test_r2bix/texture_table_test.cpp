#include "pch.h"
#include "texture_table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test_r2bix/TextureTable4Test.h"

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

			TextureTable4Test::GetInstance().Load();

			auto texture = TextureTable4Test::GetInstance().GetTexture( "blablabla" );

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "const auto texture_frame = TextureTable4Test::GetInstance().GetTexture( \"blablabla\" );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << "+ Show" << r2::linefeed2;

				for( int y = 0; texture->GetHeight() > y; ++y )
				{
					for( int x = 0; texture->GetWidth() > x; ++x )
					{
						std::cout << texture->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

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

				for( int y = 0; texture->GetHeight() > y; ++y )
				{
					for( int x = 0; texture->GetWidth() > x; ++x )
					{
						std::cout << texture->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto texture_frame = TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) );

				std::cout << r2::linefeed;

				for( int y = 0; texture_frame->GetHeight() > y; ++y )
				{
					for( int x = 0; texture_frame->GetWidth() > x; ++x )
					{
						std::cout << texture_frame->Get( x, y );
					}

					std::cout << r2::linefeed;
				}

				std::cout << r2::linefeed;

				for( int ty = texture_frame->GetMinY(), y = 0; texture_frame->GetMaxY() >= ty; ++ty, ++y )
				{
					for( int tx = texture_frame->GetMinX(), x = 0; texture_frame->GetMaxX() >= tx; ++tx, ++x )
					{
						std::cout << texture_frame->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
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
				std::cout << "+ Add Texture" << r2::linefeed2;

				EXPECT_TRUE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2::split;
				
			{
				std::cout << "+ Show" << r2::linefeed2;
				std::cout << "const auto texture = TextureTable4Test::GetInstance().GetTexture( \"TextureTable_3\" );" << r2::linefeed2;

				auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" );
				for( int y = 0; texture->GetHeight() > y; ++y )
				{
					for( int x = 0; texture->GetWidth() > x; ++x )
					{
						std::cout << texture->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				std::cout << "+ Add Texture" << r2::linefeed2;

				EXPECT_FALSE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Remove Texture" << r2::linefeed2;

				EXPECT_TRUE( TextureTable4Test::GetInstance().RemoveTexture( "TextureTable_3" ) );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Show" << r2::linefeed2;
				std::cout << "const auto texture = TextureTable4Test::GetInstance().GetTexture( \"TextureTable_3\" );" << r2::linefeed2;

				auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" );
				for( int y = 0; texture->GetHeight() > y; ++y )
				{
					for( int x = 0; texture->GetWidth() > x; ++x )
					{
						std::cout << texture->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}