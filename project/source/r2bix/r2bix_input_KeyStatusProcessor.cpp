#include "r2bix_input_KeyStatusProcessor.hpp"

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	KeyStatusProcessor::KeyStatusProcessor() : mContainer()
	{}

	void KeyStatusProcessor::Update( const MachineInputCollector& machine_input_collector )
	{
		for(
			r2bix_input::KeyCodeTypeT cur_code = r2bix_input::eKeyCode::START, end_code = r2bix_input::eKeyCode::END;
			end_code >= cur_code;
			++cur_code
		)
		{
			auto& cur_info = mContainer[cur_code];

			cur_info.Update( machine_input_collector.HasInput( cur_code ) );
		}
	}
}