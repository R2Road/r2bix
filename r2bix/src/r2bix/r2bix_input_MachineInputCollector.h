#pragma once

#include <array>
#include <bitset>

#include "r2bix_input_Constant.h"
#include "r2bix_input_ObservationKeys.h"

namespace r2bix_input
{
	class MachineInputCollector
	{
	public:
		MachineInputCollector();



		//
		//
		//
		const std::bitset<255>& GetObservationKeyStates() const
		{
			return mObservationKeyStates;
		}
		
		//
		//
		//
		void Collect();

		//
		//
		//
		void AddObservationKeys( const ObservationKeys& observation_keys );
		void RemoveObservationKeys( const ObservationKeys& observation_keys );

		//
		//
		//
		bool HasInput( const KeyCodeTypeT key_value ) const
		{
			return mObservationKeyStates.test( key_value );
		}

	private:
		std::array<KeyCodeTypeT, 255> mObservationKeyList;
		std::bitset<255> mObservationKeyStates;
	};
}