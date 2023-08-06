#include "director_scheduler_test.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

#include "r2bix/r2bix_director_Config.h"
#include "r2bix/r2bix_director_Scheduler.h"

namespace director_scheduler_test
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
			std::cout << r2tm::split;

			{
				DECLARATION_MAIN( auto config( r2bix_director::Config{ 0, 0, r2bix_director::Config::eScheduleType::Infinite, 10, 20 } ) )
				DECLARATION_MAIN( r2bix_director::Scheduler scheduler( config, [](float) {}, []() {} ) );
			}

			std::cout << r2tm::split;

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}