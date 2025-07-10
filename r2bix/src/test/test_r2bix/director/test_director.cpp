#include "test_director.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "r2bix_Director.h"

namespace test_director
{
	r2tm::TitleFunctionT Size::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director : Size";
		};
	}
	r2tm::DoFunctionT Size::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_director::Config c );
			DECLARATION_MAIN( r2bix::Director d( c ) );

			LS();

			{
				OUTPUT_SIZE( d );

				LF();

				OUTPUT_BINARY( d );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}