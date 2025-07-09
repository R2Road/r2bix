#include "test_director__defarred_task_queue.h"

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



	r2tm::TitleFunctionT Process::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : DefarredTaskQueue : Process";
		};
	}
	r2tm::DoFunctionT Process::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_director::DefarredTaskQueue q );
			DECLARATION_MAIN( int i = 0; );

			LS();

			{
				PROCESS_MAIN( q.Add( [&i](){ ++i; } ) );
				PROCESS_MAIN( q.Add( [&i](){ ++++i; } ) );

				LF();

				EXPECT_FALSE( q.Empty() );
				EXPECT_EQ( 2, q.Size() );
			}

			LS();

			{
				OUTPUT_SUBJECT( "Process는 쌓인 Task를 모두 호출 하고 삭제한다." );

				LF();

				PROCESS_MAIN( q.Process() );

				LF();

				EXPECT_EQ( 3, i );
			}

			LS();

			{
				OUTPUT_COMMENT( "Process()가 불리면 Q가 Swap 된다." );
				OUTPUT_COMMENT( "위에서 처리를 담당한 Q의 확인은 Process를 한번 더 부르고 확인 한다." );

				LF();

				PROCESS_MAIN( q.Process() );

				LF();

				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT TaskBringsTask::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : DefarredTaskQueue : Task Brings Task";
		};
	}
	r2tm::DoFunctionT TaskBringsTask::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			OUTPUT_SUBJECT( "Task 처리 과정에서 Task가 추가된 경우" );

			LS();

			DECLARATION_MAIN( r2bix_director::DefarredTaskQueue q );
			DECLARATION_MAIN( int i = 0 );

			LS();

			{
				PROCESS_MAIN( q.Add( [&q, &i]()
				{
					++i;
					q.Add( [&q, &i]()
					{
						++++++i;
					} );
				} ) );

				LF();

				EXPECT_FALSE( q.Empty() );
				EXPECT_EQ( 1, q.Size() );
			}

			LS();

			{
				OUTPUT_COMMENT( "Process()는 Q Swap 이후에" );
				OUTPUT_COMMENT( "다음 Q에 Task가 남아있다면 즉시 다음 Q를 처리한다." );

				LF();

				PROCESS_MAIN( q.Process() );

				LF();

				EXPECT_EQ( 4, i );

				LF();

				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			{
				PROCESS_MAIN( q.Process() );

				LF();

				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}