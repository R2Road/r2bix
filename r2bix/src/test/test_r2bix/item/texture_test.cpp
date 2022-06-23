#include "texture_test.h"

#include <string>

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_constant.h"

#include "r2bix/r2render_Texture.h"
#include "r2bix/r2render_TextureFrame.h"

#include "test/Utility4Test.h"

namespace texture_test
{
	r2cm::iItem::TitleFuncT FillCharacterAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill Character All";
		};
	}
	r2cm::iItem::DoFuncT FillCharacterAll::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2render::Texture texture( 30, 20 ) );
			PROCESS_MAIN( texture.FillCharacterAll( '1' ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureCharacter( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT FillCharacter::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillCharacter";
		};
	}
	r2cm::iItem::DoFuncT FillCharacter::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2render::Texture texture( 30, 20 ) );
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



	r2cm::iItem::TitleFuncT FillColorAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill Color All";
		};
	}
	r2cm::iItem::DoFuncT FillColorAll::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			OUTPUT_VALUE( fore );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_BrightWhite );
			OUTPUT_VALUE( back );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2render::Texture texture( 5, 5 ) );
			PROCESS_MAIN( texture.FillColorAll( fore | back ) );
			PROCESS_SUB( texture.FillCharacterAll( 'A' ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureColor( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT FillColor ::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillColor";
		};
	}
	r2cm::iItem::DoFuncT FillColor::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_BrightWhite );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2render::Texture texture( 10, 10 ) );
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



	r2cm::iItem::TitleFuncT FillColorWithMask::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : FillColorWithMask";
		};
	}
	r2cm::iItem::DoFuncT FillColorWithMask::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

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

			DECLARATION_MAIN( r2render::Texture texture( 10, 10, 'A' ) );
			PROCESS_SUB( texture.FillColorAll( base_color ) );
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



	r2cm::iItem::TitleFuncT BlendColor::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : BlendColor";
		};
	}
	r2cm::iItem::DoFuncT BlendColor::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_Aqua );
			DECLARATION_MAIN( const auto new_fore = r2base::eForegroundColor::FG_Red );
			OUTPUT_VALUE( new_fore );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( r2render::Texture texture( 10, 10 ) );
			PROCESS_SUB( texture.FillCharacterAll( 'A' ) );
			PROCESS_SUB( texture.FillColorAll( fore | back ) );
			PROCESS_MAIN( texture.BlendColor( 0, 0, new_fore ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTextureColor( texture );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT InitWithChars_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 1";
		};
	}
	r2cm::iItem::DoFuncT InitWithChars_1::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2render::Texture texture( "Init With Chars" ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT InitWithChars_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 2";
		};
	}
	r2cm::iItem::DoFuncT InitWithChars_2::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2render::Texture texture( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggghh" ) );

			std::cout << r2cm::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT InitWithChars_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 3";
		};
	}
	r2cm::iItem::DoFuncT InitWithChars_3::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2render::Texture texture( 8, 8, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2render::Texture texture( 3, 3, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				std::cout << r2cm::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT InitWithChars_4::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Init With Chars 4";
		};
	}
	r2cm::iItem::DoFuncT InitWithChars_4::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2render::Texture texture( 7, 7, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

			std::cout << r2cm::linefeed;

			Utility4Test::DrawTexture( texture );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}