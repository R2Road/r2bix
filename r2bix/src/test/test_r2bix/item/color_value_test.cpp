#include "color_value_test.h"

#include "r2cm/r2cm_constant.h"
#include "r2cm/r2cm_Inspector.h"

#include "r2bix/r2base_ColorValue.h"

#include "test/Utility4Test.h"

namespace color_value_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				OUTPUT_VALUE( r2base::DefaultColorValue );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( r2base::eForegroundColor::FG_White, r2base::GetForegroundColor( r2base::DefaultColorValue ) );
				EXPECT_EQ( r2base::eBackgroundColor::BG_Black, r2base::GetBackgroundColor( r2base::DefaultColorValue ) );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
				DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_Gray );
				DECLARATION_MAIN( r2base::ColorValue color_value{ fore | back } );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( fore | back, color_value );
				EXPECT_EQ( fore, r2base::GetForegroundColor( color_value ) );
				EXPECT_EQ( back, r2base::GetBackgroundColor( color_value ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT ColorOption_Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Color Option : Generate";
		};
	}
	r2cm::iItem::DoFuncT ColorOption_Generate::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2cm::linefeed;

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2base::ColorOption op );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2base::ColorOption op( r2base::eColorFlag::CF_Foreground | r2base::eColorFlag::CF_Background ) );
				EXPECT_EQ( uint8_t( -1 ), op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2base::ColorOption op( r2base::eColorFlag::CF_Foreground ) );
				EXPECT_EQ( uint8_t( -1 ) >> 4, op.GetMask() );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( r2base::ColorOption op( r2base::eColorFlag::CF_Background ) );
				EXPECT_EQ( ( uint8_t( -1 ) >> 4 ) << 4, op.GetMask() );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}