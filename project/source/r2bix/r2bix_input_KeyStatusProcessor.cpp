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

			if( machine_input_collector.GetObservationKeySignals()[cur_code] )
			{
				switch( cur_info.GetStep() )
				{
				case eKeyStep::None:
					cur_info.Set( eKeyStep::Push, true );
					break;

				case eKeyStep::Push:
					cur_info.Set( eKeyStep::Pressed, true );
					break;

				case eKeyStep::Pressed:
					cur_info.Set( eKeyStep::Pressed, false );
					break;

				case eKeyStep::Release:
					cur_info.Set( eKeyStep::Push, true );
					break;

				}
			}
			else
			{
				switch( cur_info.GetStep() )
				{
				case eKeyStep::None:
					cur_info.Set( eKeyStep::None, false );
					break;

				case eKeyStep::Push:
				case eKeyStep::Pressed:
					cur_info.Set( eKeyStep::Release, true );
					break;

				case eKeyStep::Release:
					cur_info.Set( eKeyStep::None, true );
					break;
				}
			}
		}
	}
}