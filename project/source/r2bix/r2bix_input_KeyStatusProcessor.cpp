#include "r2bix_input_KeyStatusProcessor.hpp"

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	KeyStatusProcessor::KeyStatusProcessor() : mContainer()
	{}

	void KeyStatusProcessor::Update( const MachineInputCollector& machine_input_collector )
	{
		for(
			r2bix_input::KeyCodeTypeT cur_code = r2bix_input::eKeyCode::START;
			r2bix_input::eKeyCode::END >= cur_code;
			++cur_code
		)
		{
			mContainer[cur_code].Update( machine_input_collector.HasInput( cur_code ) );
		}
	}
}