#include "texture_test.h"

#include <string>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "r2bix/r2bix_render_Texture.h"
#include "r2bix/r2bix_render_TextureFrame.h"

#include "test/Utility4Test.h"

namespace texture_test
{
	r2cm::iItem::TitleFunctionT FillCharacterAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill Character All";
		};
	}
	r2cm::iItem::DoFunctionT FillCharacterAll::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix_render::Texture texture( 30, 20 ) );
			PROCESS_MAIN( texture.FillCharacterAll( '1' ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureCharacter( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT FillCharacter::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillCharacter";
		};
	}
	r2cm::iItem::DoFunctionT FillCharacter::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix_render::Texture texture( 30, 20 ) );
			PROCESS_MAIN( texture.FillCharacter( 0, 0, '0' ) );
			PROCESS_MAIN( texture.FillCharacter( texture.GetXEnd(), 0, '0' ) );
			PROCESS_MAIN( texture.FillCharacter( texture.GetXEnd(), texture.GetYEnd(), '0' ) );
			PROCESS_MAIN( texture.FillCharacter( 0, texture.GetYEnd(), '0' ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureCharacter( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT FillColorAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill Color All";
		};
	}
	r2cm::iItem::DoFunctionT FillColorAll::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			OUTPUT_VALUE( fore );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_BrightWhite );
			OUTPUT_VALUE( back );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2bix_render::Texture texture( 5, 5, 'A' ) );
			PROCESS_MAIN( texture.FillColorAll( fore | back ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureColor( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT FillColor ::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillColor";
		};
	}
	r2cm::iItem::DoFunctionT FillColor::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_BrightWhite );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10 ) );
			PROCESS_MAIN( texture.FillColor( 0, 0, fore | back ) );
			PROCESS_MAIN( texture.FillColor( texture.GetXEnd(), 0, r2base::DefaultColorValue ) );
			PROCESS_MAIN( texture.FillColor( texture.GetXEnd(), texture.GetYEnd(), back ) );
			PROCESS_MAIN( texture.FillColor( 0, texture.GetYEnd(), fore ) );
			PROCESS_SUB( texture.FillCharacterAll( 'A' ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureColor( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT FillColorWithMask::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillColorWithMask";
		};
	}
	r2cm::iItem::DoFunctionT FillColorWithMask::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( const auto base_color = r2base::eForegroundColor::FG_Aqua | r2base::eBackgroundColor::BG_Aqua );
			DECLARATION_MAIN( const auto new_fore_color = r2base::eForegroundColor::FG_Red );
			OUTPUT_VALUE( new_fore_color );
			DECLARATION_MAIN( const auto new_back_color = r2base::eBackgroundColor::BG_Red );
			OUTPUT_VALUE( new_back_color );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( const r2base::ColorMaskOption only_foregound_cmo( r2base::eColorMaskFlag::CMF_Foreground ) );
			OUTPUT_BINARY( only_foregound_cmo.GetMask() );
			DECLARATION_MAIN( const r2base::ColorMaskOption only_background_cmo( r2base::eColorMaskFlag::CMF_Background ) );
			OUTPUT_BINARY( only_background_cmo.GetMask() );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10, 'A', base_color ) );
			PROCESS_MAIN( texture.FillColorWithMask( 0, 0, new_fore_color, only_foregound_cmo ) );
			PROCESS_MAIN( texture.FillColorWithMask( 1, 0, new_fore_color, only_background_cmo ) );
			PROCESS_MAIN( texture.FillColorWithMask( 0, 1, new_back_color, only_background_cmo ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureColor( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT BlendColor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : BlendColor";
		};
	}
	r2cm::iItem::DoFunctionT BlendColor::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_Aqua );
			DECLARATION_MAIN( const auto new_fore = r2base::eForegroundColor::FG_Red );
			OUTPUT_VALUE( new_fore );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10, 'A', fore | back ) )
			PROCESS_MAIN( texture.BlendColor( 0, 0, new_fore ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureColor( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT FillCharacterDisuse::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillCharacterDisuse";
		};
	}
	r2cm::iItem::DoFunctionT FillCharacterDisuse::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_Blue );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2bix_render::Texture texture( 10, 10, 'A', fore | back ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( 0, 0, true ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( texture.GetXEnd(), 0, true ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( texture.GetXEnd(), texture.GetYEnd(), true ) );
			PROCESS_MAIN( texture.FillCharacterDisuse( 0, texture.GetYEnd(), true ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureDisuse( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT InitWithChars_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 1";
		};
	}
	r2cm::iItem::DoFunctionT InitWithChars_1::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const std::string_view str( "Init With Chars" ) );
				DECLARATION_MAIN( const r2bix_render::Texture texture( str ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( str.size(), texture.GetWidth() );
				EXPECT_EQ( 1, texture.GetHeight() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const std::string_view str( "Init\n With \nChars\n" ) );
				DECLARATION_MAIN( const r2bix_render::Texture texture( str ) );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( 6, texture.GetWidth() );
				EXPECT_EQ( 4, texture.GetHeight() );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT InitWithChars_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 2";
		};
	}
	r2cm::iItem::DoFunctionT InitWithChars_2::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix_render::Texture texture( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggghh" ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT InitWithChars_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 3";
		};
	}
	r2cm::iItem::DoFunctionT InitWithChars_3::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix_render::Texture texture( 8, 8, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix_render::Texture texture( 3, 3, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT InitWithChars_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 4";
		};
	}
	r2cm::iItem::DoFunctionT InitWithChars_4::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix_render::Texture texture( 7, 7, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

			std::cout << r2cm::linefeed;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}