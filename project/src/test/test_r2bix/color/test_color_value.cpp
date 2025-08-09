#include "test_color_value.h"

#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_Inspector.h"

#include "r2bix_ColorMaskOption.h"
#include "r2bix_ColorValue.h"
#include "helper/r2bix_helper_Printer4Texture.h"


namespace test_color_value
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUTPUT_VALUE( r2bix::DefaultColorValue );

				LF();

				EXPECT_EQ( r2bix::eForegroundColor::FG_White, r2bix::GetForegroundColor( r2bix::DefaultColorValue ) );
				EXPECT_EQ( r2bix::eBackgroundColor::BG_Black, r2bix::GetBackgroundColor( r2bix::DefaultColorValue ) );
			}

			LS();

			{
				DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
				DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_Gray );
				DECLARATION_MAIN( r2bix::ColorValue color_value{ fore | back } );

				LF();

				EXPECT_EQ( fore | back, color_value );
				EXPECT_EQ( fore, r2bix::GetForegroundColor( color_value ) );
				EXPECT_EQ( back, r2bix::GetBackgroundColor( color_value ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ColorMaskOption_Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Mask Option : Generate";
		};
	}
	r2tm::DoFunctionT ColorMaskOption_Generate::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground | r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( ( uint8_t( -1 ) >> 4 ) << 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( 0 ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ColorMaskOption_On_Off::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Mask Option : On / Off";
		};
	}
	r2tm::DoFunctionT ColorMaskOption_On_Off::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix::ColorMaskOption op( 0 ) );
			EXPECT_EQ( 0, op.GetMask() );

			LS();

			{
				std::cout << r2tm::tab << "+ Foreground" << r2tm::linefeed2;

				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Foreground ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );

				LF();

				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Foreground ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Background" << r2tm::linefeed2;

				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4 << 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );

				LF();

				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Both" << r2tm::linefeed2;

				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Foreground ) );
				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );

				LF();

				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Foreground ) );
				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ColorMaskOption_Mask::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Mask Option : Mask";
		};
	}
	r2tm::DoFunctionT ColorMaskOption_Mask::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
			OUTPUT_BINARY( uint8_t( fore ) );
			DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_Gray );
			OUTPUT_BINARY( uint8_t( back ) );

			LS();

			{
				DECLARATION_MAIN( const r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground ) );
				OUTPUT_BINARY( op.GetMask() );

				LF();

				EXPECT_EQ( fore, ( fore | back ) & op.GetMask() );
			}

			LS();

			{
				DECLARATION_MAIN( const r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Background ) );
				OUTPUT_BINARY( op.GetMask() );

				LF();

				EXPECT_EQ( back, ( fore | back ) & op.GetMask() );
			}

			LS();

			{
				DECLARATION_MAIN( const r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground | r2bix::eColorMaskFlag::CMF_Background ) );
				OUTPUT_BINARY( op.GetMask() );

				LF();

				EXPECT_EQ( ( fore | back ), ( fore | back ) & op.GetMask() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}