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
		void ClearListener();

		void AddListener( r2bix_input::Listener4Mouse* const listener );
		void RemoveListener( r2bix_input::Listener4Mouse* const listener );

		void AddListener( r2bix_input::Listener4Keyboard* const listener );
		void RemoveListener( r2bix_input::Listener4Keyboard* const listener );

		const ListenerContainer4Mouse& GetListenerContainer4Mouse() const
		{
			return mListenerContainer4Mouse;
		}
		const ListenerContainer4Keyboard& GetListenerContainer4Keyboard() const
		{
			return mListenerContainer4Keyboard;
		}



	public:
		MachineInputCollector mMachineInputCollector;

		ListenerContainer4Mouse mListenerContainer4Mouse;
		ListenerContainer4Keyboard mListenerContainer4Keyboard;
	};
}