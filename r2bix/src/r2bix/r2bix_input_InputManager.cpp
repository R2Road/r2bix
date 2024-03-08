#include "r2bix_input_InputManager.h"

#include "r2bix_input_KeyboardInputListener.h"

namespace r2bix_input
{
	InputManager::InputManager() : mMachineInputCollector()
	{}

	void InputManager::Update()
	{
		mMachineInputCollector.Collect();
		mKeyboardInputListener->Update( mMachineInputCollector.GetObservationKeyStates() );
	}



	void InputManager::AddInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		RemoveInputListener( mKeyboardInputListener );

		mKeyboardInputListener = keyboard_input_listener;

		mMachineInputCollector.AddListener( mKeyboardInputListener );
	}
	void InputManager::RemoveInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		if( nullptr == keyboard_input_listener )
		{
			return;
		}

		if( keyboard_input_listener != mKeyboardInputListener )
		{
			return;
		}

		mMachineInputCollector.RemoveListener( mKeyboardInputListener );

		mKeyboardInputListener = nullptr;
	}
}