#include "test_input___listener_4_keyboard.hpp"

#include <algorithm>

#include "r2bix_input_Listener4Keyboard.h"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

namespace test_input___listener_4_keyboard
{
	inline std::ostream& operator<<( std::ostream& o, const r2bix_input::eKeyStatus s )
	{
		return o << ( int ) s;
	}
	r2tm::TitleFunctionT ObservationKey::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "ObservationKey";
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

			EXPECT_EQ( 0, o.key_index);
			EXPECT_EQ( 0, o.key_code );
			EXPECT_EQ( r2bix_input::eKeyStatus::None, o.key_status );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ObservationKeyList_Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key List : Declaration";
		};
	}
	r2tm::DoFunctionT ObservationKeyList_Declaration::GetDoFunction() const
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

				EXPECT_EQ( 0, c[0].key_index );
				EXPECT_TRUE( r2bix_input::eKeyCode::VK_1 == c[0].key_code );
				EXPECT_TRUE( c.IsObservationKey( r2bix_input::eKeyCode::VK_1 ) );

				LF();

				EXPECT_EQ( 1, c[1].key_index );
				EXPECT_TRUE( r2bix_input::eKeyCode::VK_2 == c[1].key_code );
				EXPECT_TRUE( c.IsObservationKey( r2bix_input::eKeyCode::VK_2 ) );

				LF();

				EXPECT_FALSE( c.IsObservationKey( r2bix_input::eKeyCode::VK_3 ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT ObservationKeyList_Add::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Observation Key List : Add";
		};
	}
	r2tm::DoFunctionT ObservationKeyList_Add::GetDoFunction() const
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
					std::cout << (int)k.key_index << " : " << (int)k.key_code << r2tm::linefeed;
				}
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}