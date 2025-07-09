#include "test_texture_frame.h"

#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"
#include "helper/r2bix_helper_Printer4Texture.h"

#include "r2helper_STDPrinter4Rect.h"

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
			LS();

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			LF();

			r2bix_helper::Printer4Texture::DrawTexture( texture );

			LS();

			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			LF();

			r2bix_helper::Printer4Texture::DrawTextureFrame( frame );

			LS();

			r2helper::STDPrinter4Rect::PrintMinMax( frame.GetVisibleRect() );

			LF();

			EXPECT_EQ( &texture, frame.GetTexture() );

			EXPECT_EQ( texture.GetCharacter( 0, 0 ), frame.GetCharacter( 0, 0 ) );
			EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

			EXPECT_EQ( texture.GetCharacter( 6, 6 ), frame.GetCharacter( 6, 6 ) );
			EXPECT_EQ( '7', frame.GetCharacter( 6, 6 ) );

			LS();

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
			LS();

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );
			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			LF();

			{
				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						LF();
					}
				}
				if( 0u != cur_x )
				{
					LF();
				}
			}

			LS();

			{
				r2helper::STDPrinter4Rect::PrintMinMax( frame.GetVisibleRect() );

				LF();

				PROCESS_MAIN( frame.MoveVisibleOrigin( 2, 1 ) );
				PROCESS_MAIN( frame.ChangeVisibleSize( -3, -1 ) );

				LF();

				r2helper::STDPrinter4Rect::PrintMinMax( frame.GetVisibleRect() );

				LF();

				EXPECT_EQ( texture.GetCharacter( frame.GetMinX(), frame.GetMinY() ), frame.GetCharacter( 0, 0 ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			LS();

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
			LS();

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			LF();

			{
				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						LF();
					}
				}
				if( 0u != cur_x )
				{
					LF();
				}
			}

			LS();

			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			LF();

			{
				r2helper::STDPrinter4Rect::PrintMinMax( frame.GetVisibleRect() );

				LF();

				PROCESS_MAIN( frame.MoveVisibleOrigin( -3, -3 ) );
				PROCESS_MAIN( frame.ChangeVisibleSize( -1, -1 ) );

				LF();

				r2helper::STDPrinter4Rect::PrintMinMax( frame.GetVisibleRect() );

				LF();

				EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			LS();

			{
				PROCESS_MAIN( frame.MoveVisibleOrigin( 6, 6 ) );

				LF();

				r2helper::STDPrinter4Rect::PrintMinMax( frame.GetVisibleRect() );

				LF();

				EXPECT_EQ( '4', frame.GetCharacter( 0, 0 ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}