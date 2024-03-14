#pragma once

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	class KeyboardListener;
	class MouseListener;

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
		void AddMouseListener( r2bix_input::MouseListener* const listener );
		void RemoveMouseListener( r2bix_input::MouseListener* const listener );
		void AddKeyboardListener( r2bix_input::KeyboardListener* const listener );
		void RemoveKeyboardListener( r2bix_input::KeyboardListener* const listener );



	public:
		MachineInputCollector mMachineInputCollector;

		KeyboardListener* mKeyboardListener;
		MouseListener* mMouseListener;
	};
}