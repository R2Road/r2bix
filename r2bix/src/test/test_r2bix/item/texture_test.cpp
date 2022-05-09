#include "pch.h"
#include "texture_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_constant.h"

#include "r2bix/r2render_Texture.h"
#include "r2bix/r2render_TextureFrame.h"

#include "test/Utility4Test.h"

namespace texture_test
{
	r2cm::iItem::TitleFuncT FillAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill All";
		};
	}
	r2cm::iItem::DoFuncT FillAll::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( const r2render::Texture texture( 30, 20, '0' ) );

			std::cout << r2::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT Fill::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture : Fill";
		};
	}
	r2cm::iItem::DoFuncT Fill::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( r2render::Texture texture( 30, 20 ) );
			PROCESS_MAIN( texture.Fill( 0, 0, '0' ) );
			PROCESS_MAIN( texture.Fill( texture.GetXEnd(), 0, '0' ) );
			PROCESS_MAIN( texture.Fill( texture.GetXEnd(), texture.GetYEnd(), '0' ) );
			PROCESS_MAIN( texture.Fill( 0, texture.GetYEnd(), '0' ) );

			std::cout << r2::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2::split;

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
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( const r2render::Texture texture( "Init With Chars" ) );

			std::cout << r2::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2::split;

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
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( const r2render::Texture texture( 5, "aaaaaaabbbbbbbcccddddeeeeeeeefffggghh" ) );

			std::cout << r2::split;

			Utility4Test::DrawTexture( texture );

			std::cout << r2::split;

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
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const r2render::Texture texture( 8, 8, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2::split;

			{
				DECLARATION_MAIN( const r2render::Texture texture( 3, 3, '#', "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

				std::cout << r2::linefeed;

				Utility4Test::DrawTexture( texture );
			}

			std::cout << r2::split;

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
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( const r2render::Texture texture( 7, 7, "aaaaaaabbbbbbbcccddddeeeeeeeefffggg" ) );

			std::cout << r2::linefeed;

			Utility4Test::DrawTexture( texture );

			std::cout << r2::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}