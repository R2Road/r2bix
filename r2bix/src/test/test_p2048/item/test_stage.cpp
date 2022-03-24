#include "pch.h"
#include "test_stage.h"

#include <conio.h>
#include <Windows.h>

#include "base/r2base_Director.h"
#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "p2048/p2048_Stage.h"

void PrintStage( const p2048::Stage& stage )
{
	int val = -1;
	for( uint32_t y = 0; stage.GetHeight() > y; ++y )
	{
		for( uint32_t x = 0; stage.GetWidth() > x; ++x )
		{
			val = stage.Get( x, y );

			if( -1 == val )
			{
				std::cout << "X";
			}
			else
			{
				std::cout << val;
			}

			std::cout << r2::tab;
		}

		std::cout << r2::linefeed;
	}
}

namespace test_stage
{
	r2cm::iItem::TitleFuncT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Basic";
		};
	}
	r2cm::iItem::DoFuncT Basic::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 7, 5 ) );
			EXPECT_EQ( 7, stage.GetWidth() );
			EXPECT_EQ( 5, stage.GetHeight() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( stage.Add( 2, 2, 64 ) );
				EXPECT_EQ( 64, stage.Get( 2, 2 ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}