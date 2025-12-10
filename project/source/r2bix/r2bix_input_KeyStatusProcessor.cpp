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
				switch( cur_info.status )
				{
				case eKeyStatus::None:
					cur_info.status = eKeyStatus::Push;
					cur_info.changed = true;
					break;

				case eKeyStatus::Push:
					cur_info.status = eKeyStatus::Pressed;
					cur_info.changed = true;
					break;

				case eKeyStatus::Pressed:
					//cur_info.status = eKeyStatus::Pressed;
					cur_info.changed = false;
					break;

				case eKeyStatus::Release:
					cur_info.status = eKeyStatus::Push;
					cur_info.changed = true;
					break;

				}
			}
			else
			{
				switch( cur_info.status )
				{
				case eKeyStatus::None:
					//cur_info.status = eKeyStatus::None;
					cur_info.changed = false;
					break;

				case eKeyStatus::Push:
				case eKeyStatus::Pressed:
					cur_info.status = eKeyStatus::Release;
					cur_info.changed = true;
					break;

				case eKeyStatus::Release:
					cur_info.status = eKeyStatus::None;
					cur_info.changed = true;
					break;
				}
			}
		}
	}
}