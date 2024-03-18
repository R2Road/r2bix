#pragma once

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	class Listener4Keyboard;
	class Listener4Mouse;

	class InputManager
	{
	public:
		InputManager( const short offset_x, const short offset_y );



		//
		//
		//
		void Update();



		//
		//
		//
		void ClearListener()
		{
			mKeyboardListener = nullptr;
			mMouseListener = nullptr;
		}
		void AddMouseListener( r2bix_input::Listener4Mouse* const listener );
		void RemoveMouseListener( r2bix_input::Listener4Mouse* const listener );
		void AddKeyboardListener( r2bix_input::Listener4Keyboard* const listener );
		void RemoveKeyboardListener( r2bix_input::Listener4Keyboard* const listener );



	public:
		MachineInputCollector mMachineInputCollector;

		Listener4Keyboard* mKeyboardListener;
		Listener4Mouse* mMouseListener;
	};
}