#include "r2bix_input_InputManager.h"

#include "r2bix_input_KeyboardListener.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	InputManager::InputManager( const short offset_x, const short offset_y ) :
		  mMachineInputCollector( offset_x, offset_y )
		, mKeyboardListener( nullptr )
		, mMouseListener( nullptr )
	{}

	void InputManager::Update()
	{
		//
		// 입력 수집
		//
		mMachineInputCollector.Collect();

		//
		// 키 상태 업데이트
		//
		if( mMouseListener )
		{
			mMouseListener->Update( mMachineInputCollector.GetObservationKeyStates(), mMachineInputCollector.GetCursorPoint() );
		}
		if( mKeyboardListener )
		{
			mKeyboardListener->Update( mMachineInputCollector.GetObservationKeyStates() );
		}
	}



	void InputManager::AddMouseListener( r2bix_input::Listener4Mouse* const listener )
	{
		RemoveMouseListener( listener );

		mMouseListener = listener;

		mMachineInputCollector.AddObservationKeys( listener->GetObservationKeys() );
	}
	void InputManager::RemoveMouseListener( r2bix_input::Listener4Mouse* const listener )
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
	void InputManager::AddKeyboardListener( r2bix_input::KeyboardListener* const listener )
	{
		RemoveKeyboardListener( mKeyboardListener );

		mKeyboardListener = listener;

		mMachineInputCollector.AddObservationKeys( mKeyboardListener->GetObservationKeys() );
	}
	void InputManager::RemoveKeyboardListener( r2bix_input::KeyboardListener* const listener )
	{
		if( nullptr == listener )
		{
			return;
		}

		if( listener != mKeyboardListener )
		{
			return;
		}

		mMachineInputCollector.RemoveObservationKeys( mKeyboardListener->GetObservationKeys() );

		mKeyboardListener = nullptr;
	}
}