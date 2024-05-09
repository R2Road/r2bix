#include "director_defarred_task_queue_test.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "r2bix_director_DefarredTaskQueue.h"

namespace director_defarred_task_queue_test
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : DefarredTaskQueue : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECLARATION_MAIN( r2bix_director::DefarredTaskQueue q );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Size::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : DefarredTaskQueue : Size";
		};
	}
	r2tm::DoFunctionT Size::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_director::DefarredTaskQueue q );

			LS();

			{
				OUTPUT_SIZE( q );

				LF();

				OUTPUT_BINARIES( &q, 1 );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Add::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : DefarredTaskQueue : Add";
		};
	}
	r2tm::DoFunctionT Add::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_director::DefarredTaskQueue q );

			LS();

			{
				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			{
				PROCESS_MAIN( q.Add( [](){} ) );

				LF();

				EXPECT_FALSE( q.Empty() );
				EXPECT_EQ( 1, q.Size() );
			}

			LS();

			{
				PROCESS_MAIN( q.Add( [](){} ) );

				LF();

				EXPECT_FALSE( q.Empty() );
				EXPECT_EQ( 2, q.Size() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}