#include "test_texture_frame.h"

#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"
#include "helper/r2bix_helper_Printer4Texture.h"

#include "r2printer_std_rect.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "test/2d/TextureTable4Test.h"

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

namespace test_texture_frame
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

			DECL_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			LF();

			r2bix_helper::Printer4Texture::DrawTexture( texture );

			LS();

			DECL_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			LF();

			r2bix_helper::Printer4Texture::DrawTextureFrame( frame );

			LS();

			r2printer::STD_Rect::Print( frame.GetVisibleRect() );

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

			DECL_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );
			DECL_MAIN( r2bix_render::TextureFrame frame( &texture ) );

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
				r2printer::STD_Rect::Print( frame.GetVisibleRect() );

				LF();

				PROC_MAIN( frame.MoveVisibleOrigin( 2, 1 ) );
				PROC_MAIN( frame.ChangeVisibleSize( -3, -1 ) );

				LF();

				r2printer::STD_Rect::Print( frame.GetVisibleRect() );

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

			DECL_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

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

			DECL_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			LF();

			{
				r2printer::STD_Rect::Print( frame.GetVisibleRect() );

				LF();

				PROC_MAIN( frame.MoveVisibleOrigin( -3, -3 ) );
				PROC_MAIN( frame.ChangeVisibleSize( -1, -1 ) );

				LF();

				r2printer::STD_Rect::Print( frame.GetVisibleRect() );

				LF();

				EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			LS();

			{
				PROC_MAIN( frame.MoveVisibleOrigin( 6, 6 ) );

				LF();

				r2printer::STD_Rect::Print( frame.GetVisibleRect() );

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