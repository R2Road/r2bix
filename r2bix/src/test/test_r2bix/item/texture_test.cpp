#include "texture_test.h"

#include <string>

#include "r2bix_render_Texture.h"
#include "r2bix_render_TextureFrame.h"
#include "r2bix_helper/r2bix_helper_Printer4Texture.h"
#include "r2bix_helper/r2bix_helper_STDPrinter4Texture.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace texture_test
{
	r2tm::TitleFunctionT FillCharacterAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill Character All";
		};
	}
	r2tm::DoFunctionT FillCharacterAll::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Texture texture( 30, 20 ) );
			PROCESS_MAIN( texture.FillCharacterAll( '1' ) );

			LS();

			r2bix_helper::Printer4Texture::DrawTextureCharacter( texture );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillCharacter::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillCharacter";
		};
	}
	r2tm::DoFunctionT FillCharacter::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Texture texture( 30, 20 ) );
			PROCESS_MAIN( texture.FillCharacter( 0, 0, '0' ) );
			PROCESS_MAIN( texture.FillCharacter( texture.GetXEnd(), 0, '0' ) );
			PROCESS_MAIN( texture.FillCharacter( texture.GetXEnd(), texture.GetYEnd(), '0' ) );
			PROCESS_MAIN( texture.FillCharacter( 0, texture.GetYEnd(), '0' ) );

			LS();

			r2bix_helper::Printer4Texture::DrawTextureCharacter( texture );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillStringAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill String All";
		};
	}
	r2tm::DoFunctionT FillStringAll::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Texture texture( 31, 21 ) );
			PROCESS_MAIN( texture.FillStringAll( "fill string all~!" ));

			LS();

			r2bix_helper::Printer4Texture::DrawTextureCharacter( texture );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillString::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill String";
		};
	}
	r2tm::DoFunctionT FillString::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Texture texture( 31, 21, '=' ) );
			PROCESS_MAIN( texture.FillString( "fill string~!" ) );

			LS();

			r2bix_helper::Printer4Texture::DrawTextureCharacter( texture );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillColorAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill Color All";
		};
	}
	r2tm::DoFunctionT FillColorAll::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
			OUTPUT_VALUE( fore );
			DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_BrightWhite );
			OUTPUT_VALUE( back );

			LF();

			DECLARATION_MAIN( r2bix_render::Texture texture( 5, 5, 'A' ) );
			PROCESS_MAIN( texture.FillColorAll( fore | back ) );

			LS();

			PROCESS_MAIN( r2bix_helper::STDPrinter4Texture::DrawTextureColor( texture ) );

			LS();

			PROCESS_MAIN( r2bix_helper::Printer4Texture::DrawTexture( texture ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillColor ::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillColor";
		};
	}
	r2tm::DoFunctionT FillColor::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_BrightWhite );

			LF();

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10 ) );
			PROCESS_MAIN( texture.FillColor( 0, 0, fore | back ) );
			PROCESS_MAIN( texture.FillColor( texture.GetXEnd(), 0, r2bix::DefaultColorValue ) );
			PROCESS_MAIN( texture.FillColor( texture.GetXEnd(), texture.GetYEnd(), back ) );
			PROCESS_MAIN( texture.FillColor( 0, texture.GetYEnd(), fore ) );
			PROCESS_SUB( texture.FillCharacterAll( 'A' ) );

			LS();

			PROCESS_MAIN( r2bix_helper::STDPrinter4Texture::DrawTextureColor( texture ) );

			LS();

			PROCESS_MAIN( r2bix_helper::Printer4Texture::DrawTexture( texture ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillColorWithMask::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillColorWithMask";
		};
	}
	r2tm::DoFunctionT FillColorWithMask::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( const auto base_color = r2bix::eForegroundColor::FG_Aqua | r2bix::eBackgroundColor::BG_Aqua );
			DECLARATION_MAIN( const auto new_fore_color = r2bix::eForegroundColor::FG_Red );
			OUTPUT_VALUE( new_fore_color );
			DECLARATION_MAIN( const auto new_back_color = r2bix::eBackgroundColor::BG_Red );
			OUTPUT_VALUE( new_back_color );

			LF();

			DECLARATION_MAIN( const r2bix::ColorMaskOption only_foregound_cmo( r2bix::eColorMaskFlag::CMF_Foreground ) );
			OUTPUT_BINARY( only_foregound_cmo.GetMask() );
			DECLARATION_MAIN( const r2bix::ColorMaskOption only_background_cmo( r2bix::eColorMaskFlag::CMF_Background ) );
			OUTPUT_BINARY( only_background_cmo.GetMask() );

			LF();

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10, 'A', base_color ) );
			PROCESS_MAIN( texture.FillColorWithMask( 0, 0, new_fore_color, only_foregound_cmo ) );
			PROCESS_MAIN( texture.FillColorWithMask( 1, 0, new_fore_color, only_background_cmo ) );
			PROCESS_MAIN( texture.FillColorWithMask( 0, 1, new_back_color, only_background_cmo ) );

			LS();

			PROCESS_MAIN( r2bix_helper::STDPrinter4Texture::DrawTextureColor( texture ) );

			LS();

			PROCESS_MAIN( r2bix_helper::Printer4Texture::DrawTexture( texture ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT BlendColor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : BlendColor";
		};
	}
	r2tm::DoFunctionT BlendColor::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_Aqua );
			DECLARATION_MAIN( const auto new_fore = r2bix::eForegroundColor::FG_Red );
			OUTPUT_VALUE( new_fore );

			LF();

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10, 'A', fore | back ) )
			PROCESS_MAIN( texture.BlendColor( 0, 0, new_fore ) );

			LS();

			PROCESS_MAIN( r2bix_helper::STDPrinter4Texture::DrawTextureColor( texture ) );

			LS();

			PROCESS_MAIN( r2bix_helper::Printer4Texture::DrawTexture( texture ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT FillCharacterDisuse::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillCharacterDisuse";
		};
	}
	r2tm::DoFunctionT FillCharacterDisuse::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_Blue );

			LF();

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10, 'A', fore | back ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( 0, 0, true ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( texture.GetXEnd(), 0, true ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( texture.GetXEnd(), texture.GetYEnd(), true ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( 0, texture.GetYEnd(), true ) );

			LS();

			PROCESS_MAIN( r2bix_helper::STDPrinter4Texture::DrawTextureDisuse( texture ) );

			LS();

			PROCESS_MAIN( r2bix_helper::Printer4Texture::DrawTexture( texture ) );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InitWithChars_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 1";
		};
	}
	r2tm::DoFunctionT InitWithChars_1::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECLARATION_MAIN( const std::string_view str( "Init With Chars" ) );
				DECLARATION_MAIN( const r2bix_render::Texture texture( str ) );

				LF();

				EXPECT_EQ( str.size(), texture.GetWidth() );
				EXPECT_EQ( 1, texture.GetHeight() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( texture );
			}

			LS();

			{
				DECLARATION_MAIN( const std::string_view str( "Init\n With \nChars\n" ) );
				DECLARATION_MAIN( const r2bix_render::Texture texture( str ) );

				LF();

				EXPECT_EQ( 6, texture.GetWidth() );
				EXPECT_EQ( 4, texture.GetHeight() );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( texture );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InitWithChars_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 2";
		};
	}
	r2tm::DoFunctionT InitWithChars_2::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const r2bix_render::Texture texture( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggghh" ) );

			LS();

			r2bix_helper::Printer4Texture::DrawTexture( texture );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InitWithChars_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 3";
		};
	}
	r2tm::DoFunctionT InitWithChars_3::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECLARATION_MAIN( const r2bix_render::Texture texture( 8, 8, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( texture );
			}

			LS();

			{
				DECLARATION_MAIN( const r2bix_render::Texture texture( 3, 3, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				LF();

				r2bix_helper::Printer4Texture::DrawTexture( texture );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT InitWithChars_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 4";
		};
	}
	r2tm::DoFunctionT InitWithChars_4::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const r2bix_render::Texture texture( 7, 7, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

			LF();

			r2bix_helper::Printer4Texture::DrawTexture( texture );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}