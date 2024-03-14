#pragma once

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	class KeyboardInputListener;
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
			mKeyboardInputListener = nullptr;
			mMouseListener = nullptr;
		}
		void AddMouseListener( r2bix_input::MouseListener* const listener );
		void RemoveMouseListener( r2bix_input::MouseListener* const listener );
		void AddInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener );
		void RemoveInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener );



	public:
		MachineInputCollector mMachineInputCollector;

		KeyboardInputListener* mKeyboardInputListener;
		MouseListener* mMouseListener;
	};
}