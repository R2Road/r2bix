#include "test_p2048_stage.h"

#include <conio.h>
#include <iomanip>

#include "r2bix_Director.h"
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

			LF();
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
			LS();

			DECLARATION_MAIN( const uint32_t width = 4 );
			DECLARATION_MAIN( const uint32_t height = 3 );
			DECLARATION_MAIN( p2048::Stage stage( width, height ) );

			LS();
			{
				EXPECT_EQ( width, stage.GetWidth() );
				EXPECT_EQ( height, stage.GetHeight() );
			}

			LS();

			{
				PROCESS_MAIN( PrintStage( stage ) );
			}

			LS();

			{
				EXPECT_EQ( width - 1, stage.GetMaxX() );
				EXPECT_EQ( height - 1, stage.GetMaxY() );
				EXPECT_EQ( width * height, stage.Size() );
			}

			LS();

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
			LS();

			DECLARATION_MAIN( p2048::Stage stage( 4, 3 ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Add" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 2, 2, 64 ) );
				EXPECT_EQ( 64, stage.GetNumber( 2, 2 ) );

				PrintStage( stage );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Remove" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Remove( 2, 2 ) );
				EXPECT_EQ( 0, stage.GetNumber( 2, 2 ) );

				PrintStage( stage );
			}

			LS();

			{
				PROCESS_MAIN( stage.Add( 1, 1, 1 ) );
				PROCESS_MAIN( stage.Add( 1, 2, 1 ) );
				PROCESS_MAIN( stage.Add( 1, 3, 1 ) );

				PrintStage( stage );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Clear All" << r2tm::linefeed2;

				PROCESS_MAIN( stage.ClearAll() );
				EXPECT_EQ( 0, stage.GetNumber( 1, 1 ) );
				EXPECT_EQ( 0, stage.GetNumber( 1, 2 ) );
				EXPECT_EQ( 0, stage.GetNumber( 1, 3 ) );

				PrintStage( stage );
			}

			LS();

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
			LS();

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );

			LS();

			{
				EXPECT_TRUE( stage.IsIn( 0, 0 ) );
				EXPECT_TRUE( stage.IsIn( 1, 0 ) );
				EXPECT_TRUE( stage.IsIn( 1, 1 ) );
				EXPECT_TRUE( stage.IsIn( 0, 1 ) );
			}

			LS();

			{
				EXPECT_FALSE( stage.IsIn( -1, -1 ) );
				EXPECT_FALSE( stage.IsIn( -1, 2 ) );
				EXPECT_FALSE( stage.IsIn( 2, -1 ) );
				EXPECT_FALSE( stage.IsIn( 2, 2 ) );

				LF();

				EXPECT_FALSE( stage.IsIn( -1, 0 ) );
				EXPECT_FALSE( stage.IsIn( 2, 0 ) );
				EXPECT_FALSE( stage.IsIn( 0, 2 ) );
			}

			LS();

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
			LS();

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );
			EXPECT_EQ( 0, stage.GetNumberSpaceCount() );

			LS();

			{
				std::cout << r2tm::tab << "+ Add New" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 0, 0, 7 ) );
				EXPECT_EQ( 1, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 3, stage.GetEmptySpaceCount() );

				LF();

				PROCESS_MAIN( stage.Add( 0, 1, 7 ) );
				PROCESS_MAIN( stage.Add( 1, 0, 7 ) );
				EXPECT_EQ( 3, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 1, stage.GetEmptySpaceCount() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Over Write" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 0, 1, 7 ) );
				EXPECT_EQ( 3, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 1, stage.GetEmptySpaceCount() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Remove" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Remove( 0, 1 ) );
				EXPECT_EQ( 2, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 2, stage.GetEmptySpaceCount() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Full" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Add( 0, 1, 7 ) );
				PROCESS_MAIN( stage.Add( 1, 1, 7 ) );
				EXPECT_EQ( 4, stage.GetNumberSpaceCount() );
				EXPECT_EQ( 0, stage.GetEmptySpaceCount() );

				LF();

				EXPECT_TRUE( stage.IsFull() );
			}

			LS();

			{
				PROCESS_MAIN( stage.Remove( 0, 1 ) );
				EXPECT_FALSE( stage.IsFull() );
			}

			LS();

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
			LS();

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Lock" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Lock( 0, 0 ) );

				LF();

				EXPECT_TRUE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );

				LF();

				PROCESS_MAIN( stage.Lock( 0, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 0 ) );

				LF();

				EXPECT_TRUE( stage.IsLock( 0, 1 ) );
				EXPECT_TRUE( stage.IsLock( 1, 1 ) );
				EXPECT_TRUE( stage.IsLock( 1, 0 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ ClearAllFlags" << r2tm::linefeed2;

				PROCESS_MAIN( stage.ClearAllFlags() );

				LF();

				EXPECT_FALSE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ ClearAll" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Lock( 0, 0 ) );
				PROCESS_MAIN( stage.Lock( 0, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 0 ) );
				PROCESS_MAIN( stage.ClearAll() );

				LF();

				EXPECT_FALSE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );
			}

			LS();

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
			LS();

			DECLARATION_MAIN( p2048::Stage stage( 2, 2 ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Lock" << r2tm::linefeed2;

				PROCESS_MAIN( stage.SetNewcomer( 0, 0 ) );

				LF();

				EXPECT_TRUE( stage.IsNewcomer( 0, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 1 ) );
				EXPECT_FALSE( stage.IsNewcomer( 0, 1 ) );

				LF();

				PROCESS_MAIN( stage.SetNewcomer( 0, 1 ) );
				PROCESS_MAIN( stage.SetNewcomer( 1, 1 ) );
				PROCESS_MAIN( stage.SetNewcomer( 1, 0 ) );

				LF();

				EXPECT_TRUE( stage.IsNewcomer( 0, 1 ) );
				EXPECT_TRUE( stage.IsNewcomer( 1, 1 ) );
				EXPECT_TRUE( stage.IsNewcomer( 1, 0 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ ClearAllFlags" << r2tm::linefeed2;

				PROCESS_MAIN( stage.ClearAllFlags() );

				LF();

				EXPECT_FALSE( stage.IsNewcomer( 0, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 0 ) );
				EXPECT_FALSE( stage.IsNewcomer( 1, 1 ) );
				EXPECT_FALSE( stage.IsNewcomer( 0, 1 ) );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ ClearAll" << r2tm::linefeed2;

				PROCESS_MAIN( stage.Lock( 0, 0 ) );
				PROCESS_MAIN( stage.Lock( 0, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 1 ) );
				PROCESS_MAIN( stage.Lock( 1, 0 ) );
				PROCESS_MAIN( stage.ClearAll() );

				LF();

				EXPECT_FALSE( stage.IsLock( 0, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 0 ) );
				EXPECT_FALSE( stage.IsLock( 1, 1 ) );
				EXPECT_FALSE( stage.IsLock( 0, 1 ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}