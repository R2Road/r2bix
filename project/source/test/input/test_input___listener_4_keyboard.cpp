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
}