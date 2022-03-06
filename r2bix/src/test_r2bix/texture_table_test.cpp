#include "pch.h"
#include "texture_table_test.h"

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "p2048/p2048table_TextureTable.h"

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

			p2048table::TextureTable::GetInstance().Load();

			auto texture = p2048table::TextureTable::GetInstance().GetTexture( "blablabla" );

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "const auto texture_frame = p2048table::TextureTable::GetInstance().GetTexture( \"blablabla\" );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << "+ Show" << r2::linefeed2;

				for( int y = 0; y < texture->GetHeight(); ++y )
				{
					for( int x = 0; x < texture->GetWidth(); ++x )
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

			p2048table::TextureTable::GetInstance().Load();

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "const auto texture = p2048table::TextureTable::GetInstance().GetTexture( \"test_texture_001\" );" << r2::linefeed2;
			}

			{
				std::cout << "+ Show" << r2::linefeed2;

				auto texture = p2048table::TextureTable::GetInstance().GetTexture( "test_texture_001" );
				for( int y = 0; y < texture->GetHeight(); ++y )
				{
					for( int x = 0; x < texture->GetWidth(); ++x )
					{
						std::cout << texture->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				{
					std::cout << "+ Declaration" << r2::linefeed2;
					std::cout << r2::tab << "const auto texture_frame = p2048table::TextureTable::GetInstance().GetTextureFrame( \"dguy_walk_1\" );" << r2::linefeed2;
				}

				{
					std::cout << "+ Show" << r2::linefeed2;

					auto texture_frame = p2048table::TextureTable::GetInstance().GetTextureFrame( "dguy_walk_1" );
					for( int y = 0; y < texture_frame->GetHeight(); ++y )
					{
						for( int x = 0; x < texture_frame->GetWidth(); ++x )
						{
							std::cout << texture_frame->Get( x, y );
						}

						std::cout << r2::linefeed;
					}
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

				EXPECT_TRUE( p2048table::TextureTable::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2::split;
				
			{
				std::cout << "+ Show" << r2::linefeed2;
				std::cout << "const auto texture = p2048table::TextureTable::GetInstance().GetTexture( \"TextureTable_3\" );" << r2::linefeed2;

				auto texture = p2048table::TextureTable::GetInstance().GetTexture( "TextureTable_3" );
				for( int y = 0; y < texture->GetHeight(); ++y )
				{
					for( int x = 0; x < texture->GetWidth(); ++x )
					{
						std::cout << texture->Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				std::cout << "+ Add Texture" << r2::linefeed2;

				EXPECT_FALSE( p2048table::TextureTable::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Remove Texture" << r2::linefeed2;

				EXPECT_TRUE( p2048table::TextureTable::GetInstance().RemoveTexture( "TextureTable_3" ) );
			}

			std::cout << r2::split;

			{
				std::cout << "+ Show" << r2::linefeed2;
				std::cout << "const auto texture = p2048table::TextureTable::GetInstance().GetTexture( \"TextureTable_3\" );" << r2::linefeed2;

				auto texture = p2048table::TextureTable::GetInstance().GetTexture( "TextureTable_3" );
				for( int y = 0; y < texture->GetHeight(); ++y )
				{
					for( int x = 0; x < texture->GetWidth(); ++x )
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