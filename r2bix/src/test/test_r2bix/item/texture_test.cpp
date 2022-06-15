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

			Utility4Test::DrawTexture( texture );

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

			Utility4Test::DrawTexture( texture );

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