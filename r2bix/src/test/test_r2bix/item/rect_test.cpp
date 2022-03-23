#include "pch.h"
#include "rect_test.h"

#include <algorithm>	
#include <conio.h>
#include <Windows.h>

#include "r2/r2_Rect_Int.h"
#include "r2cm/r2cm_eTestEndAction.h"
#include "test/test_r2bix/Utility4Test.h"

namespace rect_test
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Rect : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2::RectInt rect_0( 0, 0, 1, 1 );
			const r2::RectInt rect_1( 4, 4, 6, 6 );
			const r2::RectInt rect_2( 6, 6, 6, 6 );
			const auto rect_3 = rect_1.IntersectsWithRect( rect_2 );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "const r2::RectInt rect_0( 0, 0, 1, 1 );" << r2::linefeed;
				std::cout << r2::tab2 << "const r2::RectInt rect_1( 4, 4, 6, 6 );" << r2::linefeed;
				std::cout << r2::tab2 << "const r2::RectInt rect_2( 6, 6, 6, 6 );" << r2::linefeed;
				std::cout << r2::tab2 << "const auto rect_3 = rect_1.IntersectsWithRect( rect_2 );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				const int offset_y = 13;

				Utility4Test::DrawRect( offset_y, rect_0, '0' );
				Utility4Test::DrawRect( offset_y, rect_1, '1' );
				Utility4Test::DrawRect( offset_y, rect_2, '2' );
				Utility4Test::DrawRect( offset_y, rect_3, '3' );

				SetConsoleCursorPosition(
					GetStdHandle( STD_OUTPUT_HANDLE )
					, { 0, static_cast<short>( offset_y + std::max( { rect_1.GetMaxY(), rect_2.GetMaxY(), rect_3.GetMaxY() } ) + 1) }
				);
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}