#pragma once

#include <array>
#include <bitset>

#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	class KeyboardInputListener;

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
		void ClearListener()
		{
			mKeyboardInputListener = nullptr;
		}
		void AddListener( KeyboardInputListener* listener );
		void RemoveListener( KeyboardInputListener* listener );

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

		KeyboardInputListener* mKeyboardInputListener;
	};
}