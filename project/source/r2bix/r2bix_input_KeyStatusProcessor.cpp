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
				switch( cur_info.GetStatus() )
				{
				case eKeyStatus::None:
					cur_info.Set( eKeyStatus::Push, true );
					break;

				case eKeyStatus::Push:
					cur_info.Set( eKeyStatus::Pressed, true );
					break;

				case eKeyStatus::Pressed:
					cur_info.Set( eKeyStatus::Pressed, false );
					break;

				case eKeyStatus::Release:
					cur_info.Set( eKeyStatus::Push, true );
					break;

				}
			}
			else
			{
				switch( cur_info.GetStatus() )
				{
				case eKeyStatus::None:
					cur_info.Set( eKeyStatus::None, false );
					break;

				case eKeyStatus::Push:
				case eKeyStatus::Pressed:
					cur_info.Set( eKeyStatus::Release, true );
					break;

				case eKeyStatus::Release:
					cur_info.Set( eKeyStatus::None, true );
					break;
				}
			}
		}
	}
}