#include "color_value_test.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Inspector.h"

#include "r2bix/r2bix_ColorMaskOption.h"
#include "r2bix/r2bix_ColorValue.h"

#include "test/Utility4Test.h"

namespace color_value_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				OUTPUT_VALUE( r2bix::DefaultColorValue );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2bix::eForegroundColor::FG_White, r2bix::GetForegroundColor( r2bix::DefaultColorValue ) );
				EXPECT_EQ( r2bix::eBackgroundColor::BG_Black, r2bix::GetBackgroundColor( r2bix::DefaultColorValue ) );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
				DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_Gray );
				DECLARATION_MAIN( r2bix::ColorValue color_value{ fore | back } );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( fore | back, color_value );
				EXPECT_EQ( fore, r2bix::GetForegroundColor( color_value ) );
				EXPECT_EQ( back, r2bix::GetBackgroundColor( color_value ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT ColorMaskOption_Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Mask Option : Generate";
		};
	}
	r2cm::iItem::DoFunctionT ColorMaskOption_Generate::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground | r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( ( uint8_t( -1 ) >> 4 ) << 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2bix::ColorMaskOption op( 0 ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT ColorMaskOption_On_Off::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Mask Option : On / Off";
		};
	}
	r2cm::iItem::DoFunctionT ColorMaskOption_On_Off::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix::ColorMaskOption op( 0 ) );
			EXPECT_EQ( 0, op.GetMask() );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Foreground" << r2cm::linefeed2;

				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Foreground ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Foreground ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Background" << r2cm::linefeed2;

				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4 << 4, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Both" << r2cm::linefeed2;

				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Foreground ) );
				PROCESS_MAIN( op.On( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Foreground ) );
				PROCESS_MAIN( op.Off( r2bix::eColorMaskFlag::CMF_Background ) );
				EXPECT_EQ( 0, op.GetMask() );
				OUTPUT_BINARY( op.GetMask() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT ColorMaskOption_Mask::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Mask Option : Mask";
		};
	}
	r2cm::iItem::DoFunctionT ColorMaskOption_Mask::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const auto fore = r2bix::eForegroundColor::FG_Aqua );
			OUTPUT_BINARY( uint8_t( fore ) );
			DECLARATION_MAIN( const auto back = r2bix::eBackgroundColor::BG_Gray );
			OUTPUT_BINARY( uint8_t( back ) );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground ) );
				OUTPUT_BINARY( op.GetMask() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( fore, ( fore | back ) & op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Background ) );
				OUTPUT_BINARY( op.GetMask() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( back, ( fore | back ) & op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const r2bix::ColorMaskOption op( r2bix::eColorMaskFlag::CMF_Foreground | r2bix::eColorMaskFlag::CMF_Background ) );
				OUTPUT_BINARY( op.GetMask() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( ( fore | back ), ( fore | back ) & op.GetMask() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}