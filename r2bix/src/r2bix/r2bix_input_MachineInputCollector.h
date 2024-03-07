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
		void Collect();

		//
		//
		//
		void ClearListener()
		{
			mKeyboardInputListener = nullptr;
		}
		void AddListener( KeyboardInputListener* listener )
		{
			mKeyboardInputListener = listener;
		}
		void RemoveListener( KeyboardInputListener* listener )
		{
			if( listener == mKeyboardInputListener )
			{
				mKeyboardInputListener = nullptr;
			}
		}

		//
		//
		//
		bool HasInput( const char key_value ) const
		{
			return mObservationKeyStates.test( key_value );
		}

	private:
		std::array<char, 256> mObservationKeyList;
		std::bitset<256> mObservationKeyStates;

		KeyboardInputListener* mKeyboardInputListener;
	};
}