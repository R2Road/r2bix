#include "test_director__scheduler.hpp"

#include "r2tm/r2tm_inspector.hpp"
#include "r2tm/r2tm_ostream.hpp"

#include "r2bix_director_Config.h"
#include "r2bix_director_Scheduler.h"

namespace test_director__scheduler
{
	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Director Scheduler : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			{
				DECL_MAIN( auto config( r2bix_director::Config{ 0, 0, r2bix_director::Config::eScheduleType::Infinite, 10, 20 } ) )
				DECL_MAIN( r2bix_director::Scheduler scheduler( config, [](float) {}, []() {} ) );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}