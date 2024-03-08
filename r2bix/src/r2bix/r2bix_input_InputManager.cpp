#include "r2bix_input_InputManager.h"

namespace r2bix_input
{
	InputManager::InputManager() : mMachineInputCollector()
	{}

	void InputManager::Update()
	{
		mMachineInputCollector.Collect();
	}



	void InputManager::AddInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		mMachineInputCollector.AddListener( keyboard_input_listener );
	}
	void InputManager::RemoveInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		mMachineInputCollector.RemoveListener( keyboard_input_listener );
	}
}