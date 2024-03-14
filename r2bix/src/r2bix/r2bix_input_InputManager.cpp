#include "r2bix_input_InputManager.h"

#include "r2bix_input_KeyboardInputListener.h"
#include "r2bix_input_MouseListener.h"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputCollector( offset_x, offset_y )
		, mKeyboardInputListener( nullptr )
		, mMouseListener( nullptr )
	{}

	void InputManager::Update()
	{
		//
		// �Է� ����
		//
		mMachineInputCollector.Collect();

		//
		// Ű ���� ������Ʈ
		//
		if( mMouseListener )
		{
			mMouseListener->Update( mMachineInputCollector.GetObservationKeyStates() );
		}
		if( mKeyboardInputListener )
		{
			mKeyboardInputListener->Update( mMachineInputCollector.GetObservationKeyStates() );
		}
	}



	void InputManager::AddMouseListener( r2bix_input::MouseListener* const listener )
	{
		RemoveMouseListener( listener );

		mMouseListener = listener;

		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveMouseListener( r2bix_input::MouseListener* const listener )
	{
		if( nullptr == listener )
		{
			return;
		}

		if( listener != mMouseListener )
		{
			return;
		}

		mMachineInputCollector.RemoveObservationKeys( mMouseListener->GetObservationKeys() );

		mMouseListener = nullptr;
	}
	void InputManager::AddInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		RemoveInputListener( mKeyboardInputListener );

		mKeyboardInputListener = keyboard_input_listener;

		mMachineInputCollector.AddObservationKeys( mKeyboardInputListener->GetObservationKeys() );
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

		mMachineInputCollector.RemoveObservationKeys( mKeyboardInputListener->GetObservationKeys() );

		mKeyboardInputListener = nullptr;
	}
}