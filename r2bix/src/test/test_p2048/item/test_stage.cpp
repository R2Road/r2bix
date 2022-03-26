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

			DECLARATION_MAIN( p2048::Stage stage( 6, 5 ) );
			EXPECT_EQ( 6, stage.GetWidth() );
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


			{
				PROCESS_MAIN( stage.Remove( 2, 2 ) );
				EXPECT_EQ( -1, stage.Get( 2, 2 ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT MoveReadyTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Move Ready";
		};
	}
	r2cm::iItem::DoFuncT MoveReadyTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 5, 5 ) );
			PROCESS_MAIN( PrintStage( stage ) );

			std::cout << r2::split;

			{}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT MoveTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Move";
		};
	}
	r2cm::iItem::DoFuncT MoveTest::GetDoFunction()
	{
		return []()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_MAIN( p2048::Stage stage( 4, 4 ) );

			std::cout << r2::split;

			{
				PROCESS_MAIN( stage.Add( 0, 0, 2 ) );
				PROCESS_MAIN( stage.Add( 3, 0, 4 ) );
				PROCESS_MAIN( stage.Add( 0, 3, 8 ) );
				PROCESS_MAIN( stage.Add( 3, 3, 16 ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;


			{
				PROCESS_MAIN( stage.Move( r2::Direction4::eState::Right ) );
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}