#include "test_p2048_stage.h"

#include <conio.h>
#include <iomanip>

#include "r2bix/r2bix_Director.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_Inspector.h"

#include "p2048/p2048_Stage.h"


namespace test_p2048_stage
{
	void PrintStage( const p2048::Stage& stage )
	{
		int val = 0;
		for( uint32_t y = 0; stage.GetHeight() > y; ++y )
		{
			for( uint32_t x = 0; stage.GetWidth() > x; ++x )
			{
				val = stage.GetNumber( x, y );

				std::cout << std::setw( 2 ) << std::right << val;
				std::cout << std::setw( 1 ) << std::left; // roll back

				std::cout << r2tm::tab;
			}

			std::cout << r2tm::linefeed;
		}
	}



	r2tm::TitleFunctionT Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Generate";
		};
	}
	r2tm::DoFunctionT Generate::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( const uint32_t width = 4 );
			DECLARATION_MAIN( const uint32_t height = 3 );
			DECLARATION_MAIN( p2048::Stage stage( width, height ) );

			std::cout << r2tm::split;
			{
				EXPECT_EQ( width, stage.GetWidth() );
				EXPECT_EQ( height, stage.GetHeight() );
			}

			std::cout << r2tm::split;

			{
				PROCESS_MAIN( PrintStage( stage ) );
			}

			std::cout << r2tm::split;

			{
				EXPECT_EQ( width - 1, stage.GetMaxX() );
				EXPECT_EQ( height - 1, stage.GetMaxY() );
				EXPECT_EQ( width * height, stage.Size() );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Add_Remove_ClearAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Add, Remove, ClearAll";
		};
	}
	r2tm::DoFunctionT Add_Remove_ClearAll::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( p2048::Stage stage( 4, 3 ) );

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Add" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 2, 2, 64 ) );
				EXPECT_EQ( 64, stage.GetNumber( 2, 2 ) );

				PrintStage( stage );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Remove" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Remove( 2, 2 ) );
				EXPECT_EQ( 0, stage.GetNumber( 2, 2 ) );

				PrintStage( stage );
			}

			std::cout << r2tm::split;

			{
				PROCESS_MAIN( stage.Add( 1, 1, 1 ) );
				PROCESS_MAIN( stage.Add( 1, 2, 1 ) );
				PROCESS_MAIN( stage.Add( 1, 3, 1 ) );

				PrintStage( stage );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Clear All" << r2tm::linefeed2;

				PROCESS_MAIN( stage.ClearAll() );
				EXPECT_EQ( 0, stage.GetNumber( 1, 1 ) );
				EXPECT_EQ( 0, stage.GetNumber( 1, 2 ) );
				EXPECT_EQ( 0, stage.GetNumber( 1, 3 ) );

				PrintStage( stage );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT IsIn::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : IsIn";
		};
	}
	r2tm::DoFunctionT IsIn::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );

			std::cout << r2tm::split;

			{
				EXPECT_TRUE( stage.IsIn( 0, 0 ) );
				EXPECT_TRUE( stage.IsIn( 1, 0 ) );
				EXPECT_TRUE( stage.IsIn( 1, 1 ) );
				EXPECT_TRUE( stage.IsIn( 0, 1 ) );
			}

			std::cout << r2tm::split;

			{
				EXPECT_FALSE( stage.IsIn( -1, -1 ) );
				EXPECT_FALSE( stage.IsIn( -1, 2 ) );
				EXPECT_FALSE( stage.IsIn( 2, -1 ) );
				EXPECT_FALSE( stage.IsIn( 2, 2 ) );

				std::cout << r2tm::linefeed;

				EXPECT_FALSE( stage.IsIn( -1, 0 ) );
				EXPECT_FALSE( stage.IsIn( 2, 0 ) );
				EXPECT_FALSE( stage.IsIn( 0, 2 ) );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT NumberCount_EmptyCount_IsFull::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : NumberCount, EmptyCount, IsFull";
		};
	}
	r2tm::DoFunctionT NumberCount_EmptyCount_IsFull::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );
			EXPECT_EQ( 0, stage.GetNumberSpaceCount() );

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Add New" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 0, 0, 7 ) );
				EXPECT_EQ( 1, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 3, stage.GetEmptySpaceCount() );

				std::cout << r2tm::linefeed;

				PROCESS_MAIN( stage.Add( 0, 1, 7 ) );
				PROCESS_MAIN( stage.Add( 1, 0, 7 ) );
				EXPECT_EQ( 3, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 1, stage.GetEmptySpaceCount() );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Over Write" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 0, 1, 7 ) );
				EXPECT_EQ( 3, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 1, stage.GetEmptySpaceCount() );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Remove" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Remove( 0, 1 ) );
				EXPECT_EQ( 2, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 2, stage.GetEmptySpaceCount() );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Full" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 0, 1, 7 ) );
				PROCESS_MAIN( stage.Add( 1, 1, 7 ) );
				EXPECT_EQ( 4, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 0, stage.GetEmptySpaceCount() );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( stage.IsFull() );
			}

			std::cout << r2tm::split;

			{
				PROCESS_MAIN( stage.Remove( 0, 1 ) );
				EXPECT_FALSE( stage.IsFull() );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Lock::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Lock";
		};
	}
	r2tm::DoFunctionT Lock::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Lock" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Lock( 0, 0 ) );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );

				std::cout << r2tm::linefeed;

				PROCESS_MAIN( stage.Lock( 0, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 0 ) );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( stage.IsLock( 0, 1 ) );
				EXPECT_TRUE( stage.IsLock( 1, 1 ) );
				EXPECT_TRUE( stage.IsLock( 1, 0 ) );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ ClearAllFlags" << r2tm::linefeed2;

				PROCESS_MAIN( stage.ClearAllFlags() );

				std::cout << r2tm::linefeed;

				EXPECT_FALSE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ ClearAll" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Lock( 0, 0 ) );
				PROCESS_MAIN( stage.Lock( 0, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 0 ) );
				PROCESS_MAIN( stage.ClearAll() );

				std::cout << r2tm::linefeed;

				EXPECT_FALSE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Newcomer::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Stage : Newcomer";
		};
	}
	r2tm::DoFunctionT Newcomer::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ Lock" << r2tm::linefeed2;

				PROCESS_MAIN( stage.SetNewcomer( 0, 0 ) );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( stage.IsNewcomer( 0, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 1 ) );
				EXPECT_FALSE( stage.IsNewcomer( 0, 1 ) );

				std::cout << r2tm::linefeed;

				PROCESS_MAIN( stage.SetNewcomer( 0, 1 ) );
				PROCESS_MAIN( stage.SetNewcomer( 1, 1 ) );
				PROCESS_MAIN( stage.SetNewcomer( 1, 0 ) );

				std::cout << r2tm::linefeed;

				EXPECT_TRUE( stage.IsNewcomer( 0, 1 ) );
				EXPECT_TRUE( stage.IsNewcomer( 1, 1 ) );
				EXPECT_TRUE( stage.IsNewcomer( 1, 0 ) );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ ClearAllFlags" << r2tm::linefeed2;

				PROCESS_MAIN( stage.ClearAllFlags() );

				std::cout << r2tm::linefeed;

				EXPECT_FALSE( stage.IsNewcomer( 0, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 1 ) );
				EXPECT_FALSE( stage.IsNewcomer( 0, 1 ) );
			}

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "+ ClearAll" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Lock( 0, 0 ) );
				PROCESS_MAIN( stage.Lock( 0, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 0 ) );
				PROCESS_MAIN( stage.ClearAll() );

				std::cout << r2tm::linefeed;

				EXPECT_FALSE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}