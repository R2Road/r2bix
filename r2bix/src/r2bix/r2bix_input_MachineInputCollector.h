#pragma once

#include <vector>

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

	private:
		KeyboardInputListener* mKeyboardInputListener;
	};
}