#include "texture_frame_test.h"

#include "r2bix/r2bix_render_Texture.h"
#include "r2bix/r2bix_render_TextureFrame.h"
#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "test/test_r2bix/TextureTable4Test.h"

namespace
{
	const r2bix_render::Texture& GetDummyTexture()
	{
		static const r2bix_render::Texture texture( 7,
			"1111111"
			"1222222"
			"1233333"
			"1234444"
			"1234555"
			"1234566"
			"1234567"
		);

		return texture;
	}

	void PrintRectInfo( const r2::RectInt& rect )
	{
		std::cout << r2tm::tab << "rect min, max :" << " " << rect.GetMinX() << " " << rect.GetMinY() << " " << rect.GetMaxX() << " " << rect.GetMaxY() << r2tm::linefeed;
	}
}

namespace texture_frame_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			std::cout << r2tm::linefeed;

			r2bix_helper::Printer4Texture::DrawTexture( texture );

			std::cout << r2tm::split;

			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			std::cout << r2tm::linefeed;

			r2bix_helper::Printer4Texture::DrawTextureFrame( frame );

			std::cout << r2tm::split;

			PrintRectInfo( frame.GetVisibleRect() );

			std::cout << r2tm::linefeed;

			EXPECT_EQ( &texture, frame.GetTexture() );

			EXPECT_EQ( texture.GetCharacter( 0, 0 ), frame.GetCharacter( 0, 0 ) );
			EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

			EXPECT_EQ( texture.GetCharacter( 6, 6 ), frame.GetCharacter( 6, 6 ) );
			EXPECT_EQ( '7', frame.GetCharacter( 6, 6 ) );

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT VisibleRect_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 1";
		};
	}
	r2tm::DoFunctionT VisibleRect_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );
			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			std::cout << r2tm::linefeed;

			{
				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2tm::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2tm::linefeed;
				}
			}

			std::cout << r2tm::split;

			{
				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2tm::linefeed;

				PROCESS_MAIN( frame.MoveVisibleOrigin( 2, 1 ) );
				PROCESS_MAIN( frame.ChangeVisibleSize( -3, -1 ) );

				std::cout << r2tm::linefeed;

				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( texture.GetCharacter( frame.GetMinX(), frame.GetMinY() ), frame.GetCharacter( 0, 0 ) );

				std::cout << r2tm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT VisibleRect_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 2";
		};
	}
	r2tm::DoFunctionT VisibleRect_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			std::cout << r2tm::linefeed;

			{
				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2tm::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2tm::linefeed;
				}
			}

			std::cout << r2tm::split;

			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			std::cout << r2tm::linefeed;

			{
				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2tm::linefeed;

				PROCESS_MAIN( frame.MoveVisibleOrigin( -3, -3 ) );
				PROCESS_MAIN( frame.ChangeVisibleSize( -1, -1 ) );

				std::cout << r2tm::linefeed;

				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

				std::cout << r2tm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			std::cout << r2tm::split;

			{
				PROCESS_MAIN( frame.MoveVisibleOrigin( 6, 6 ) );

				std::cout << r2tm::linefeed;

				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2tm::linefeed;

				EXPECT_EQ( '4', frame.GetCharacter( 0, 0 ) );

				std::cout << r2tm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}