#include "test_input___observation_key_flags.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "r2bix_input_ObservationKeyFlags.hpp"

namespace test_input___observation_key_flags
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key Flags : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				OUT_SUBJECT( "생성자 : 기본" );

				LF();

				DECL_MAIN( r2bix_input::ObservationKeyFlags f );

				LF();

				OUT_SUBJECT( "전체 Flags 출력" );

				LF();

				{
					int i = 0;
					for(
						r2bix_input::KeyCodeTypeT cur_code = r2bix_input::eKeyCode::START;
						r2bix_input::eKeyCode::END >= cur_code;
						++cur_code
					)
					{
						std::cout << f.IsObservationKey( cur_code );

						++i;
						if( ( i % 32 ) == 0 )
						{
							LF();
						}
					}
				}

				LF();
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Size_Binary::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key Flags : Size / Binary";
		};
	}
	r2tm::DoFunctionT Size_Binary::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECL_MAIN( r2bix_input::ObservationKeyFlags f );

				LF();

				OUT_SIZE( f );

				LF();

				OUT_BINARY( f );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Add_Remove::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key Flags : Add / Remove";
		};
	}
	r2tm::DoFunctionT Add_Remove::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( r2bix_input::ObservationKeyFlags f );

			SS();

			{
				EXPECT_FALSE( f.IsObservationKey( r2bix_input::eKeyCode::VK_0 ) );
			}

			SS();

			{
				OUT_SUBJECT( "Add" );

				LF();

				PROC_MAIN( f.Add( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_TRUE( f.IsObservationKey( r2bix_input::eKeyCode::VK_0 ) );

				LF();

				PROC_MAIN( f.Add( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_TRUE( f.IsObservationKey( r2bix_input::eKeyCode::VK_0 ) );
			}

			SS();

			{
				OUT_SUBJECT( "Remove" );

				LF();

				PROC_MAIN( f.Remove( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_TRUE( f.IsObservationKey( r2bix_input::eKeyCode::VK_0 ) );

				LF();

				PROC_MAIN( f.Remove( r2bix_input::eKeyCode::VK_0 ) );
				EXPECT_FALSE( f.IsObservationKey( r2bix_input::eKeyCode::VK_0 ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}