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

			DECLARATION_MAIN( const auto fore = r2base::eForegroundColor::FG_Aqua );
			DECLARATION_MAIN( const auto back = r2base::eBackgroundColor::BG_Gray );
			DECLARATION_MAIN( r2base::ColorValue color_value{ fore | back } );

			std::cout << r2cm::split;

			{
				EXPECT_EQ( fore | back, color_value );
				EXPECT_EQ( fore, r2base::GetForegroundColor( color_value ) );
				EXPECT_EQ( back, r2base::GetBackgroundColor( color_value ) );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}