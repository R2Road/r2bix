#include "test_director__defarred_task_queue.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "r2bix_director_DefarredTaskQueue.h"

namespace test_director__defarred_task_queue
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
				DECL_MAIN( r2bix_director::DefarredTaskQueue q );
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

			DECL_MAIN( r2bix_director::DefarredTaskQueue q );

			LS();

			{
				OUT_SIZE( q );

				LF();

				OUT_BINARIES( &q, 1 );
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

			DECL_MAIN( r2bix_director::DefarredTaskQueue q );

			LS();

			{
				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			{
				PROC_MAIN( q.Add( [](){} ) );

				LF();

				EXPECT_FALSE( q.Empty() );
				EXPECT_EQ( 1, q.Size() );
			}

			LS();

			{
				PROC_MAIN( q.Add( [](){} ) );

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

			DECL_MAIN( r2bix_director::DefarredTaskQueue q );
			DECL_MAIN( int i = 0; );

			LS();

			{
				PROC_MAIN( q.Add( [&i](){ ++i; } ) );
				PROC_MAIN( q.Add( [&i](){ ++++i; } ) );

				LF();

				EXPECT_FALSE( q.Empty() );
				EXPECT_EQ( 2, q.Size() );
			}

			LS();

			{
				OUT_SUBJECT( "Process는 쌓인 Task를 모두 호출 하고 삭제한다." );

				LF();

				PROC_MAIN( q.Process() );

				LF();

				EXPECT_EQ( 3, i );
			}

			LS();

			{
				OUT_COMMENT( "Process()가 불리면 Q가 Swap 된다." );
				OUT_COMMENT( "위에서 처리를 담당한 Q의 확인은 Process를 한번 더 부르고 확인 한다." );

				LF();

				PROC_MAIN( q.Process() );

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

			OUT_SUBJECT( "Task 처리 과정에서 Task가 추가된 경우" );

			LS();

			DECL_MAIN( r2bix_director::DefarredTaskQueue q );
			DECL_MAIN( int i = 0 );

			LS();

			{
				PROC_MAIN( q.Add( [&q, &i]()
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
				OUT_COMMENT( "Process()는 Q Swap 이후에" );
				OUT_COMMENT( "다음 Q에 Task가 남아있다면 즉시 다음 Q를 처리한다." );

				LF();

				PROC_MAIN( q.Process() );

				LF();

				EXPECT_EQ( 4, i );

				LF();

				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			{
				PROC_MAIN( q.Process() );

				LF();

				EXPECT_TRUE( q.Empty() );
				EXPECT_EQ( 0, q.Size() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}