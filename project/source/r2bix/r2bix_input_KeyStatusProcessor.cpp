#include "r2bix_input_KeyStatusProcessor.hpp"

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	KeyStatusProcessor::KeyStatusProcessor() : mContainer()
	{
		mContainer.fill( eKeyStatus::None );
	}

	void KeyStatusProcessor::Update( const MachineInputCollector& machine_input_collector )
	{
		for(
			r2bix_input::KeyCodeTypeT cur_code = r2bix_input::eKeyCode::START, end_code = r2bix_input::eKeyCode::END;
			end_code >= cur_code;
			++cur_code
		)
		{
			auto& cur_status = mContainer[cur_code];

			if( machine_input_collector.GetObservationKeySignals()[cur_code] )
			{
				switch( cur_status )
				{
				case eKeyStatus::None:
					cur_status = eKeyStatus::Push;
					break;

				case eKeyStatus::Push:
					cur_status = eKeyStatus::Pressed;
					break;

				//case eKeyStatus::Pressed:
					//	break;

				}
			}
			else
			{
				switch( cur_status )
				{
				//case eKeyStatus::None:
					//	break;

				case eKeyStatus::Push:
				case eKeyStatus::Pressed:
					cur_status = eKeyStatus::Release;
					break;

				case eKeyStatus::Release:
					cur_status = eKeyStatus::None;
					break;
				}
			}
		}
	}
}