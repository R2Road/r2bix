#pragma once

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	class KeyboardInputListener;

	class InputManager
	{
	public:
		InputManager();



		//
		//
		//
		void Update();



		//
		//
		//
		void ClearListener()
		{
			mKeyboardInputListener = nullptr;
		}
		void AddInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener );
		void RemoveInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener );



	public:
		MachineInputCollector mMachineInputCollector;

		KeyboardInputListener* mKeyboardInputListener;
	};
}