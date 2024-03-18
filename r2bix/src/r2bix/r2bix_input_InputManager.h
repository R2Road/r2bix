#pragma once

#include <list>

#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	class Listener4Keyboard;
	class Listener4Mouse;

	class InputManager
	{
	public:
		using ListenerContainer4Mouse = std::list<Listener4Mouse*>;
		using ListenerContainer4Keyboard = std::list<Listener4Keyboard*>;



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
			mMouseListener.clear();
			mKeyboardListener.clear();
		}

		void AddMouseListener( r2bix_input::Listener4Mouse* const listener );
		void RemoveMouseListener( r2bix_input::Listener4Mouse* const listener );

		void AddKeyboardListener( r2bix_input::Listener4Keyboard* const listener );
		void RemoveKeyboardListener( r2bix_input::Listener4Keyboard* const listener );



	public:
		MachineInputCollector mMachineInputCollector;

		ListenerContainer4Mouse mMouseListener;
		ListenerContainer4Keyboard mKeyboardListener;
	};
}