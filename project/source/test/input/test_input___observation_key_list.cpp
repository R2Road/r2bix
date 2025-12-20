#include "test_input___observation_key_list.hpp"

#include <algorithm>

#include "r2bix_input_Listener4Keyboard.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

namespace test_input___observation_key_list
{
	inline std::ostream& operator<<( std::ostream& o, const r2bix_input::eKeyStep s )
	{
		return o << ( int ) s;
	}
	r2tm::TitleFunctionT ObservationKey::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key";
		};
	}
	r2tm::DoFunctionT ObservationKey::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( r2bix_input::ObservationKey o );

			LF();

			OUT_SIZE( o );

			LF();

			OUT_BINARY( o );

			LF();

			EXPECT_EQ( 0, o.GetKeyIndex() );
			EXPECT_EQ( 0, o.GetKeyCode() );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key List : Declaration";
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

				DECL_MAIN( r2bix_input::ObservationKeyList c );

				LF();

				OUT_SIZE( c );

				LF();

				OUT_BINARY( c );

				LF();

				EXPECT_EQ( 0, c.Size() );
			}

			LS();

			{
				OUT_SUBJECT( "생성자 : 키 리스트" );

				LF();

				DECL_MAIN( r2bix_input::ObservationKeyList c( { r2bix_input::eKeyCode::VK_1, r2bix_input::eKeyCode::VK_2 } ) );

				LF();

				OUT_SIZE( c );

				LF();

				OUT_BINARY( c );

				LF();

				EXPECT_EQ( 2, c.Size() );

				LF();

				EXPECT_EQ( 0, c[0].GetKeyIndex() );
				EXPECT_TRUE( r2bix_input::eKeyCode::VK_1 == c[0].GetKeyCode() );
				EXPECT_TRUE( c.Has( r2bix_input::eKeyCode::VK_1 ) );

				LF();

				EXPECT_EQ( 1, c[1].GetKeyIndex() );
				EXPECT_TRUE( r2bix_input::eKeyCode::VK_2 == c[1].GetKeyCode() );
				EXPECT_TRUE( c.Has( r2bix_input::eKeyCode::VK_2 ) );

				LF();

				EXPECT_FALSE( c.Has( r2bix_input::eKeyCode::VK_3 ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Add::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key List : Add";
		};
	}
	r2tm::DoFunctionT Add::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECL_MAIN( r2bix_input::ObservationKeyList c );

			LS();

			{
				OUT_SUBJECT( "Add" );

				LF();

				{
					PROC_MAIN( c.Add( r2bix_input::eKeyCode::VK_1 ) );

					LF();

					EXPECT_EQ( 1, c.Size() );
				}

				SS();

				{
					PROC_MAIN( c.Add( r2bix_input::eKeyCode::VK_2 ) );

					LF();

					EXPECT_EQ( 2, c.Size() );
				}

				SS();

				{
					PROC_MAIN( c.Add( r2bix_input::eKeyCode::VK_2 ) );

					LF();

					EXPECT_EQ( 2, c.Size() );
				}

				SS();

				{
					PROC_MAIN( c.Add( r2bix_input::eKeyCode::VK_3 ) );

					LF();

					EXPECT_EQ( 3, c.Size() );
				}
			}

			LS();

			{
				OUT_SUBJECT( "Iteration" );

				LF();

				for( const auto& k : c )
				{
					std::cout << (int)k.GetKeyIndex() << " : " << (int)k.GetKeyCode() << r2tm::linefeed;
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}